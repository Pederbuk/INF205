import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def plot_benchmark(df, title):
    plt.figure(title)
    x = np.arange(1, 11)*20
    diff = abs(df['nodes'] - df['edges'])
    
    plt.plot(x, df)
    plt.bar(x, diff, label='None', color='gray', alpha=0.5, width=10)

    plt.legend(['Nodes', 'Edges', 'Diffrence'])
    plt.xlabel('Number of nodes')
    plt.ylabel('Time (ms)')


# No solution
# data_0 = pd.read_csv('data/benchmark_none.csv', header=1)
# plot_benchmark(data_0, 'No solution')


# # Solution
# data_1 = pd.read_csv('data/benchmark_sol.csv', header=1)
# plot_benchmark(data_1, 'Solution')

data_1 = pd.read_csv('data/benchmark.csv')
data_1.plot()
# plot_benchmark(data_1, 'Solution')

plt.show()