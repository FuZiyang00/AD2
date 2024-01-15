from src.csv_stats import csv_stats
import time 

if __name__ == "__main__": 
    
    df = csv_stats("../salary.csv")

    print(f"Mean with C++ bindings: {df.c_mean()}")
    print(f"Mean with numpy: {df.nump_mean(5)}")

    print(f"Variance with C++ bindings: {df.c_variance()}")
    print(f"Mean with numpy: {df.num_variance(5)}")

    print(f"Frequency map: {df.frequency_map()}")

    

