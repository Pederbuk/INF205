import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('data/benchmark.csv')
data.plot()
plt.show()