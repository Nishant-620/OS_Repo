import java.util.Arrays;

public class Que_2 {
    public static void main(String[] args){
        
        int[] numbers = {45, 12, 89, 7, 33, 21, 56};
        int target = 33;

        
        Arrays.sort(numbers);
        System.out.println("Sorted Array: " + Arrays.toString(numbers));

    
        int resultIndex = binarySearch(numbers, target);

        if (resultIndex != -1) {
            System.out.println("Element " + target + " found at index: " + resultIndex);
        } else {
            System.out.println("Element not found.");
        }
    }

    public static int binarySearch(int[] arr, int target) {
        int low = 0;
        int high = arr.length - 1;

        while (low <= high) {
            
            int mid = low + (high - low) / 2;

            if (arr[mid] == target) {
                return mid; 
            } else if (arr[mid] < target) {
                low = mid + 1; 
            } else {
                high = mid - 1; 
            }
        }
        return -1; 
    

        
    }
}
