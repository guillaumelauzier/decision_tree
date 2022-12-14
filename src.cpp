#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// A node in the decision tree
struct Node {
  // The index of the feature to split on
  int split_idx;

  // The value to split the feature on
  double split_val;

  // The left child node
  Node* left;

  // The right child node
  Node* right;

  // The predicted value for this node
  double value;

  // Constructor for a leaf node
  Node(double value) : value(value) {}

  // Constructor for an internal node
  Node(int split_idx, double split_val, Node* left, Node* right)
      : split_idx(split_idx), split_val(split_val), left(left), right(right) {}
};

// Compute the mean of a vector of numbers
double mean(vector<double> x) {
  double sum = 0;
  for (int i = 0; i < x.size(); i++) {
    sum += x[i];
  }
  return sum / x.size();
}

// Compute the variance of a vector of numbers
double variance(vector<double> x) {
  double mean_x = mean(x);
  double sum_sq_diff = 0;
  for (int i = 0; i < x.size(); i++) {
    sum_sq_diff += pow(x[i] - mean_x, 2);
  }
  return sum_sq_diff / x.size();
}

// Split the data into two subsets based on a split value
pair<vector<vector<double>>, vector<vector<double>>> split(vector<vector<double>> X, vector<double> y, int split_idx, double split_val) {
  vector<vector<double>> X_left, X_right;
  vector<double> y_left, y_right;
  for (int i = 0; i < X.size(); i++) {
    if (X[i][split_idx] <= split_val) {
      X_left.push_back(X[i]);
      y_left.push_back(y[i]);
    } else {
      X_right.push_back(X[i]);
      y_right.push_back(y[i]);
    }
  }
  return make_pair(X_left, X_right);
}

// Recursively build the decision tree
Node* build_tree(vector<vector<double>> X, vector<double> y, int depth) {
  // Stop building the tree if we have reached the maximum depth
  if (depth == 5) {
    return new Node(mean(y));
  }

  // Find the best split point
  int best_split_idx = -1;
  double best_split_val;
  double best_gain = 0;
  for (int i = 0; i < X[0].size(); i++) {
    // Try splitting the data on each
