//  Written by Lucas Olsen for CSCI5105
//  do not modify this file


#ifndef _ML_H_
#define _ML_H_

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

///
/////  Matrix functions
///

void scale_matricies(vector<vector<double>>& mat, double scalar);

void sum_matricies(vector<vector<double>>& _ret, vector<vector<double>>& mat);

void calc_gradient(vector<vector<double>>& curr, vector<vector<double>>& orig);


///
/////  MLP class - implements a multilayer perceptron
///


class mlp
{
    public:

        mlp();

        bool is_initialized() { return initialized; };

        bool init_training(string fname, int _k, int _h);

        bool init_training(string fname, vector<vector<double>>& _V, vector<vector<double>>& _W);

        double train(double eta, int epochs);

        double validate(string fname);

        vector<int> predict(string fname);

        void set_weights(vector<vector<double>>& _V, vector<vector<double>>& _W);

        void get_weights(vector<vector<double>>& _V, vector<vector<double>>& _W);

        void update_weights(vector<vector<double>>& _dV, vector<vector<double>>& _dW);

    private:

        void forward_propogate(vector<vector<int>>& _X);

        void backward_propogate(vector<vector<double>>& _dV, vector<vector<double>>& _dW, double eta);

        bool read_data(vector<vector<int>>& _X, vector<int>& _X_labels, string fname, bool labels);

        double error_rate(vector<int>& _X_labels);

        double error_func();

        double activation_func(double x);

        /* 
        Variable explanations:
            N = number of datapoints
            D = number of features of datapoints (number of input units also)
            H = number of hidden units
            K = number of possible outputs
        */

        int n;
        int d;
        int h;
        int k;

        // Value to check if the network has been intialized
        // Does not necessarily mean trained
        bool initialized;

        // Training datapoints matrix
        // N x D matrix
        vector<vector<int>> X;

        // training data labels
        // N length vector
        vector<int> X_labels;

        // predictions matrix, stores last round of predicitons
        // N x K matrix
        vector<vector<double>> Y;

        // Hidden units matrix, stores hidden units in MLP
        // N x H + 1 matrix
        vector<vector<double>> Z;
        
        // Weights between each input unit and hidden unit
        // D + 1 x H matrix (includes bias)
        vector<vector<double>> W;
        
        // Weights between each hidden unit and output unit
        // H + 1 x K matrix (includes bias)
        vector<vector<double>> V;
};


#endif