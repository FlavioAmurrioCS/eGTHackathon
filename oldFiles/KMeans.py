from sklearn.decomposition import TruncatedSVD
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.pipeline import make_pipeline
from sklearn.preprocessing import Normalizer
from sklearn.cluster import KMeans, MiniBatchKMeans
from time import time
from sklearn import metrics


dataset = fileToList("file.txt")
def fileToList(filename):
    data = []
    with open(filename, 'r') as f:
        data = f.readlines()
    return data


vectorizer = TfidfVectorizer(max_df=0.5, min_df=2, stop_words='english')
# vectorizer = TfidfVectorizer(max_df=0.5, max_features=opts.n_features,
#                                  min_df=2, stop_words='english',
#                                  use_idf=opts.use_idf)



X = vectorizer.fit_transform(dataset)

svd = TruncatedSVD(2)
# svd = TruncatedSVD(opts.n_components)




normalizer = Normalizer(copy=False)
lsa = make_pipeline(svd, normalizer)

X = lsa.fit_transform(X)

explained_variance = svd.explained_variance_ratio_.sum()
print("Explained variance of the SVD step: {}%".format(
        int(explained_variance * 100)))

print()

km = KMeans(n_clusters=7, init='k-means++', max_iter=100, n_init=1)


print("Clustering sparse data with %s" % km)
t0 = time()
km.fit(X)
print("done in %0.3fs" % (time() - t0))
print()

# print("Homogeneity: %0.3f" % metrics.homogeneity_score(labels, km.labels_))
# print("Completeness: %0.3f" % metrics.completeness_score(labels, km.labels_))
# print("V-measure: %0.3f" % metrics.v_measure_score(labels, km.labels_))
# print("Adjusted Rand-Index: %.3f"
#       % metrics.adjusted_rand_score(labels, km.labels_))
print("Silhouette Coefficient: %0.3f"
      % metrics.silhouette_score(X, km.labels_, sample_size=1000))

print()



if not True:
    print("Top terms per cluster:")

    if 2:
        original_space_centroids = svd.inverse_transform(km.cluster_centers_)
        order_centroids = original_space_centroids.argsort()[:, ::-1]
    else:
        order_centroids = km.cluster_centers_.argsort()[:, ::-1]

    terms = vectorizer.get_feature_names()
    for i in range(7):
        print("Cluster %d:" % i, end='')
        for ind in order_centroids[i, :10]:
            print(' %s' % terms[ind], end='')
        print()