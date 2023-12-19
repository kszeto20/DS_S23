#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>

#include "image.h"
#include "priority_queue.h"

using std::cout; using std::endl;
// ===================================================================================================

// distance field method functions
double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image);

// visualization style helper functions
Color Rainbow(double distance, double max_distance);
Color GreyBands(double distance, double max_distance, int num_bands);

// ===================================================================================================

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " input.ppm output.ppm distance_field_method visualization_style" << std::endl;
        exit(1);
    }

    // open the input image
    Image<Color> input;
    if (!input.Load(argv[1])) {
        std::cerr << "ERROR: Cannot open input file: " << argv[1] << std::endl;
        exit(1);
    }

    // a place to write the distance values
    Image<DistancePixel> distance_image;
    distance_image.Allocate(input.Width(),input.Height());

    // calculate the distance field (each function returns the maximum distance value)
    double max_distance = 0;
    if (std::string(argv[3]) == std::string("naive_method")) {
        max_distance = NaiveDistanceFieldMethod(input,distance_image);
    } else if (std::string(argv[3]) == std::string("improved_method")) {
        max_distance = ImprovedDistanceFieldMethod(input,distance_image);
    } else if (std::string(argv[3]) == std::string("pq_with_map")) {
        max_distance = FastMarchingMethod(input,distance_image);
    } else if (std::string(argv[3]) == std::string("pq_with_hash_table")) {
        // EXTRA CREDIT: implement FastMarchingMethod with a hash table
    } else {
        std::cerr << "ERROR: Unknown distance field method: " << argv[3] << std::endl;
        exit(1);
    }

    // convert distance values to a visualization
    Image<Color> output;
    output.Allocate(input.Width(),input.Height());
    for (int i = 0; i < input.Width(); i++) {
        for (int j = 0; j < input.Height(); j++) {
        double v = distance_image.GetPixel(i,j).getValue();
        if (std::string(argv[4]) == std::string("greyscale")) {
            output.SetPixel(i,j,GreyBands(v,max_distance*1.01,1));
        } else if (std::string(argv[4]) == std::string("grey_bands")) {
            output.SetPixel(i,j,GreyBands(v,max_distance,4));
        } else if (std::string(argv[4]) == std::string("rainbow")) {
            output.SetPixel(i,j,Rainbow(v,max_distance));
        } else {
        // EXTRA CREDIT: create other visualizations 
        std::cerr << "ERROR: Unknown visualization style" << std::endl;
        exit(0);
        }
        }
    }
    // save output
    if (!output.Save(argv[2])) {
        std::cerr << "ERROR: Cannot save to output file: " << argv[2] << std::endl;
        exit(1);
    }

    return 0;
}

// ===================================================================================================

double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
    int w = input.Width();
    int h = input.Height();
    // return the maximum distance value
    double answer = 0;
    // loop over the pixels in the input image
    for (int i = 0; i < w; i++)  {
        for (int j = 0; j < h; j++) {
            double closest = -1;      
            // loop over all other pixels in the input image
            for (int i2 = 0; i2 < w; i2++)  {
                for (int j2 = 0; j2 < h; j2++) {
                    const Color& c = input.GetPixel(i2,j2);      
                    // skip all pixels that are not black
                    if (!c.isBlack()) continue;
                        // calculate the distance between the two pixels
                        double distance = sqrt((i-i2)*(i-i2) + (j-j2)*(j-j2));
                    // store the closest distance to a black pixel
                    if (closest < 0 || distance < closest) {
                        closest = distance;
                    }
                }
            }
            assert (closest >= 0);
            answer = std::max(answer,closest);
            // save the data to the distance image
            DistancePixel& p = distance_image.GetPixel(i,j);
            p.setValue(closest);
        }
    }
    return answer;
}

double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
    int w = input.Width();
    int h = input.Height();
    // return the maximum distance value
    double answer = 0;

    std::vector<std::pair<int, int>> b_sq; // vector of pairs of coordinates of black squares
    for (int i = 0; i < w; i++) { // loop to find all the black squares
        for (int j = 0; j < h; j++) {
            const Color& c = input.GetPixel(i, j);
            if (c.isBlack()) { // if it's a black square
                b_sq.push_back(std::make_pair(i, j)); // add to the vector
            }
        }
    }
    // assumption: image will always have at least one non-black pixel
    // for each pixel in the image
    for (int width = 0; width < w; width++) {
        for (int height = 0; height < h; height++) {
            double closest = -1;
            // for each black square in the table
            for (long unsigned int i = 0; i < b_sq.size(); i++) {
                int w_coor = b_sq[i].first;
                int h_coor = b_sq[i].second;
                // if the square is a black square - set value to 0
                if (width == w_coor && height == h_coor) { closest = 0; }
                else {
                    // else if the square is not black -- calculate the distance
                    double distance = sqrt((width-w_coor)*(width-w_coor) + (height-h_coor)*(height-h_coor));
                    if (distance < closest || closest < 0) { // if distance is closer
                        closest = distance; // update closest counter
                    }
                }
                
            }
            // after all black squares are checked
            assert(closest >= 0);
            answer = std::max(answer, closest); // find biggest distance
            DistancePixel& p = distance_image.GetPixel(width, height);
            p.setValue(closest); // set the correct distance to the pixel value
        }
    }

    return answer;
}

double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
    int w = input.Width();
    int h = input.Height();
    // return the maximum distance value

    std::vector<const DistancePixel*> known_pixels; // to keep track of black curve dots + coords popped from the queue
    std::set<const DistancePixel*> known_set;
    std::vector<DistancePixel*> prop_pixels; // pixels that can be modified (to_propagate)
    std::set<DistancePixel*> prop_set; // helper set to prop_pixels

    // Step 1: collect all black pixels and set their distance values to 0, 
    //          everything else gets a huge distance val
    for (int i = 0; i < w; i++) { // loop to find all the black squares
        for (int j = 0; j < h; j++) {
            const Color& c = input.GetPixel(i, j);
            double toSet = 0;
            DistancePixel& p = distance_image.GetPixel(i, j);
            p.setX(i); // set proper coordinates
            p.setY(j);
            if (c.isBlack()) { // if is a black square
                known_pixels.push_back(&p); // push back into vector of known pixels
                known_set.insert(&p);
            }
            else {
                toSet = (double)(w*h*2); // make large distance value
            }
            p.setValue(toSet); // set values for newly initialized pixel
        }
    }


    // Step 2: go to all the neighbors of each of the black square and assign them dist values
    long unsigned int new_known;
    for (new_known = 0; new_known < known_pixels.size(); new_known++) { // for each black value
        int w_coor = known_pixels[new_known]->getX();
        int h_coor = known_pixels[new_known]->getY();

        for (int i = -1; i < 2; i++) { // check row above, row of, and row below
            if (w_coor + i >= 0 && w_coor + i < w) { // bounds check
                for (int j = -1; j < 2; j++) { // check col left, col of, col right
                    if ((h_coor + j >= 0 && h_coor + j < h)) { // bounds check
                        // grab pixel
                        DistancePixel& p = distance_image.GetPixel(w_coor + i, h_coor +j);
                        // if pixel has an already set value -- black spot --> don't do anything
                        std::set<const DistancePixel*>::iterator itr = known_set.find(&p);
                        if (itr != known_set.end()) { continue; }
                        // else, find the distance between the neighbor and the black spot
                        double distance = sqrt((i)*(i) + (j)*(j));
                        if (distance < p.getValue()) { // if the distance is less than current value, update
                            //answer = std::max(distance, answer); // update max value counter
                            p.setValue(distance);
                        }
                        // add the value to a set of indexes that still needed to be propogated
                        std::pair<std::set<DistancePixel*>::iterator, bool> added = prop_set.insert(&p);
                        if (added.second == true) { prop_pixels.push_back(&p); }
                    }
                }
            }
        }
    }
    
    // Step 3: make the priority queue with the neighbors of the initially black spots only
    DistancePixel_PriorityQueue prio(prop_pixels);

    // Step 4: pop off values from the priority queue + process until no more values
    while (prio.size() != 0) { // while there are values to pop
        const DistancePixel* lowest = prio.top(); // get the top value
        known_pixels.push_back(lowest); // it is now immutable because it has the lowest priority number
        known_set.insert(lowest);

        int w_coor = lowest->getX();
        int h_coor = lowest->getY();
        double curr_val = lowest->getValue();
        int num_added = 0;

        // same as initial checking of black spot neighbors 
        for (int i = -1; i < 2; i++) { // check neighbor rows
            if (w_coor + i >= 0 && w_coor + i < w) { // bounds check
                for (int j = -1; j < 2; j++) { // check neighbor cols
                    if ((h_coor + j >= 0 && h_coor + j < h)) { // bounds check
                        // grab pixel
                        DistancePixel& p = distance_image.GetPixel(w_coor + i, h_coor + j);
                        // if pixel is an already set + immutable value --> skip over it
                        std::set<const DistancePixel*>::iterator itr = known_set.find(&p);
                        if (itr != known_set.end()) { continue; }
                        // else, find distance between the neighboor and current square
                        double distance = sqrt((i)*(i) + (j)*(j));
                        // if dist(neighbor to newly popped) + dist(newly popped + its own value) < neighbor stored value
                        if (distance + curr_val < p.getValue()) {
                            //answer = std::max(distance + curr_val, answer); // update max value counter
                            p.setValue(distance + curr_val); // update value
                        }
                        // add the value to a set of indexes that still needed to be propogated
                        std::pair<std::set<DistancePixel*>::iterator, bool> added = prop_set.insert(&p);
                        if (added.second == true) { prop_pixels.push_back(&p); num_added++; }
                    }
                }
            }
        }

        // add all new neighbors back into priority queue
        for (long unsigned int last_pind = prop_pixels.size() - num_added; last_pind < prop_pixels.size(); last_pind++) { 
            prio.push(prop_pixels[last_pind]);
        }
        new_known++;
        prio.pop();
    }

    double answer = 0;
    // get max distance value
    for (int i = 0; i < w; i++) { // loop to find all the black squares
        for (int j = 0; j < h; j++) {
            DistancePixel& p = distance_image.GetPixel(i, j);
            answer = std::max(answer, p.getValue());
        }
    }

    return answer;
}

// ===================================================================================================

Color Rainbow(double distance, double max_distance) {
    Color answer;
    if (distance < 0.001) {
        // black
        answer.r = 0; answer.g = 0; answer.b = 0;
    } else if (distance < 0.2*max_distance) {
        // blue -> cyan
        double tmp = distance * 5.0 / max_distance;
        answer.r = 0;
        answer.g = tmp*255;
        answer.b = 255;
    } else if (distance < 0.4*max_distance) {
        // cyan -> green
        double tmp = (distance-0.2*max_distance) * 5.0 / max_distance;
        answer.r = 0;
        answer.g = 255;
        answer.b = (1-tmp*tmp)*255;
    } else if (distance < 0.6*max_distance) {
        // green -> yellow
        double tmp = (distance-0.4*max_distance) * 5.0 / max_distance;
        answer.r = sqrt(tmp)*255;
        answer.g = 255;
        answer.b = 0;
    } else if (distance < 0.8*max_distance) {
        // yellow -> red
        double tmp = (distance-0.6*max_distance) * 5.0 / max_distance;
        answer.r = 255;
        answer.g = (1-tmp*tmp)*255;
        answer.b = 0;
    } else if (distance < max_distance) {
        // red -> white
        double tmp = (distance-0.8*max_distance) * 5.0 / max_distance;
        answer.r = 255;
        answer.g = tmp*255;
        answer.b = tmp*255;
    } else {
        // white
        answer.r = answer.g = answer.b = 255;
    }  
    return answer;
}

Color GreyBands(double distance, double max_value, int num_bands) {
    Color answer;
    if (distance < 0.001) {
        // red
        answer.r = 255; answer.g = 0; answer.b = 0;
    } else {
        // shades of grey
        answer.r = answer.g = answer.b = int(num_bands*256*distance/double(max_value)) % 256;
    }  
    return answer;
}

// ===================================================================================================