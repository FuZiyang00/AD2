import numpy as np
import pandas as pd
import time
import sys
sys.path.append('../build')
import statistica_module
import csvparser_module

def timer(my_function):
    def wrapper(*args, **kwargs):
        t1 = time.time()
        result = my_function(*args, **kwargs)
        t2 = time.time()
        print(f"{my_function.__name__} ran in {t2 - t1:.3f} sec")
        return result
    return wrapper

class CSV:
    def __init__(self, inputfile):
        self.csv = csvparser_module.CSV_parser(inputfile)
        self.table = self.csv.getCSVData()
        self.data = pd.read_csv(inputfile)
        self.column = self.table[3] # indexing the column I want to analysise
        self.stats = statistica_module.StatisticalOperation(self.column, self.table)


    @timer
    def c_mean(self): 
        '''
        Use the CSVParser instance to compute the mean
        Return: the mean of the column
        '''
        return self.stats.mean()
    
    @timer
    def nump_mean(self, col_n):
        '''
        Compute the mean using numpy
        Parameters: col: index of column
        Return: the mean of the column
        ''' 
        return np.mean(self.data.iloc[:, col_n]) 
    
    @timer
    def c_variance(self):
        '''
        Use the CSVParser instance to compute the variance
        Return: the variance of the column
        '''
        return self.stats.variance()
    
    @timer
    def num_variance(self, col_n):
        return np.var(self.data.iloc[:, col_n])
    
    @timer 
    def frequency_map(self):
        '''
        Return the frequency map of the unique observations in the column
        '''
        return self.stats.FrequencyCount()

    
