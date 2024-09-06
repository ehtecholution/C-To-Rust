
// Quicksort implementation for sorting arrays of any type that implements Ord trait
fn quicksort<T: Ord>(arr: &mut [T], low: isize, high: isize) {
    // Base case: if low index is less than high index
    if low < high {
        // Get the partition index
        let pi = partition(arr, low, high);
        
        // Recursively sort the left and right subarrays
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Partition function to divide the array around a pivot
fn partition<T: Ord>(arr: &mut [T], low: isize, high: isize) -> isize {
    // Choose the rightmost element as pivot
    let pivot = high;
    // Initialize the index of smaller element
    let mut i = low - 1;

    // Traverse through all elements
    for j in low..high {
        // If current element is smaller than or equal to pivot
        if arr[j as usize] < arr[pivot as usize] {
            // Increment index of smaller element
            i += 1;
            // Swap elements
            arr.swap(i as usize, j as usize);
        }
    }

    // Place the pivot in its correct position
    arr.swap((i + 1) as usize, pivot as usize);
    // Return the partition index
    i + 1
}
