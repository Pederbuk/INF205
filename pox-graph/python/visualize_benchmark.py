import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


def plot_benchmark(df, title):
    for col in df:
        df[col] = df[col].rolling(100).mean()

    df.plot(title=title)
    plt.xlabel('Number of nodes')
    plt.ylabel('Time (ns)')


# No solution
data_0 = pd.read_csv('pox-graph/data/benchmark_none.csv')
plot_benchmark(data_0, 'No solution')


# Solution
data_1 = pd.read_csv('pox-graph/data/benchmark_sol.csv')
plot_benchmark(data_1, 'Solution')

# Mixed solution
data_2 = pd.read_csv('pox-graph/data/benchmark_mix.csv')
plot_benchmark(data_2, 'Mixed solutions')

# Preformance increase
preformance_inc = pd.DataFrame() 
preformance_inc['nodes / nodes_para'] = data_0['nodes'] / data_0['nodes_para']
preformance_inc['edges / edges_para'] = data_0['edges'] / data_0['edges_para']
preformance_inc.plot(title='Preformance increase')
plt.xlabel('Number of nodes')


plt.show()