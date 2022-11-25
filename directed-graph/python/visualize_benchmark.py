import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


def plot_benchmark(df, title):
    df['x'] = np.arange(1, 11)*20
    df.plot('x', title=title)
    plt.xlabel('Number of nodes')
    plt.ylabel('Time (ms)')


# No solution
data_0 = pd.read_csv('data/benchmark_none.csv')
plot_benchmark(data_0, 'No solution')


# Solution
data_1 = pd.read_csv('data/benchmark_sol.csv')
plot_benchmark(data_1, 'Solution')

# Benchmark
data_1 = pd.read_csv('data/benchmark.csv')
plot_benchmark(data_1, 'Benchmark')


plt.show()