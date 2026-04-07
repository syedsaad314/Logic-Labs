/*
 * Topic: Array Manipulation & Sliding Window Technique
 * * Problem Statement: 
 * Given an array of integers and a number 'k', find the maximum sum of any contiguous 
 * subarray of size 'k'. Doing this with nested loops is too slow (O(N*k)). We use the 
 * sliding window technique to do it in a single pass (O(N)), which is much more optimized.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int getMaxSubarraySum(const vector<int>& arr, int k) {
    if (arr.size() < k) {
        cout << "Error: Array size is smaller than the window size.\n";
        return -1;
    }

    int maxSum = 0;
    int currentWindowSum = 0;

    // Calculate the sum of the very first window
    for (int i = 0; i < k; ++i) {
        currentWindowSum += arr[i];
    }
    maxSum = currentWindowSum;

    // Slide the window across the array
    for (int i = k; i < arr.size(); ++i) {
        // Add the next element, remove the first element of the previous window
        currentWindowSum += arr[i] - arr[i - k];
        maxSum = max(maxSum, currentWindowSum);
    }

    return maxSum;
}

int main() {
    vector<int> data = {2, 1, 5, 1, 3, 2};
    int windowSize = 3;

    cout << "--- Sliding Window Optimizer ---\n";
    cout << "Dataset: [2, 1, 5, 1, 3, 2]\n";
    cout << "Window Size: " << windowSize << "\n";
    
    int result = getMaxSubarraySum(data, windowSize);
    cout << "Maximum Contiguous Sum: " << result << "\n";

    return 0;
}