#Importing required modules
 
from sklearn.datasets import load_digits
from sklearn.decomposition import PCA
from sklearn.cluster import KMeans, DBSCAN
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# Load Data
data = load_digits().data
pca = PCA(2)
 
# Transform the data
df = pca.fit_transform(data)
# print(df)

# Read data
df_ = pd.read_csv("dataset/locations.csv", names=("hour", "latitude", "longitude", "speed"))
df = pd.DataFrame(df_, columns=["latitude", "longitude"]).values.tolist()
df = np.array(df)
# print(df)

# Initialize the class object
# Kmeans
""" kmeans = KMeans(n_clusters=5, max_iter=100).fit(df)

# DBscan
# clustering = DBSCAN(eps=3, min_samples=2).fit(df)
 
# Predict the labels of clusters.
labels = kmeans.labels_

# Getting the Centroids
centroids = kmeans.cluster_centers_ """

# ---
# For serial: _s
# For parallel: _p
centroids_ = pd.read_csv("p_sso/centroids.csv", names=["latitude", "longitude"])
centroids = np.array(centroids_[["latitude", "longitude"]].values.tolist())
labels_ = pd.read_csv("p_sso/labels.csv", names=["label"])
labels = np.array(labels_["label"].values.tolist())
print(labels)
# ---

# Getting unique labels
u_labels = np.unique(labels)
print(u_labels)

# Plotting the results:
for i in u_labels:
    plt.scatter(df[labels == i , 0] , df[labels == i , 1] , label = i)
plt.scatter(centroids[:,0], centroids[:,1], s=80, color='k')
plt.legend()
plt.show()

# Run:
# python graphic_clusters.py