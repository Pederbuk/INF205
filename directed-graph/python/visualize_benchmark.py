import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


def plot_benchmark(df, title):
    for col in df:
        df[col] = df[col].rolling(20).mean()

    df.plot(title=title)
    plt.xlabel('Number of nodes')
    plt.ylabel('Time (ns)')


# # No solution
# data_0 = pd.read_csv('directed-graph/data/benchmark_none.csv')
# plot_benchmark(data_0, 'No solution')


# # Solution
# data_1 = pd.read_csv('directed-graph/data/benchmark_sol.csv')
# plot_benchmark(data_1, 'Solution')

# Benchmark
data_1 = pd.read_csv('directed-graph/data/benchmark.csv')
plot_benchmark(data_1, 'Benchmark')


plt.show()