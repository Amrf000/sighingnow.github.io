---
title: 社区发现与K-means聚类
author: He Tao
date: 2015-04-24
tag: [聚类, 社会网络]
category: 社会网络
layout: post
---

将机器学习中的概率算法模型引入社区发现和网络图划分算法的研究--以K-means算法为例。

摘要
-----

社区发现(Community Detection)作为社会网络科学的经典问题之一，长期以来一直受到领域内研究者的广泛关注，近二十多年来，社区发现以及社交网络图的划分算法一直是定义期刊、会议的热点之一。本文旨在阐述如何将机器学习的概率算法模型引入社区发现和网络图划分的研究中来，通过合理利用成熟的机器学习技术来改善传统算法面对超大规模社交网络时在效率、性能和准确性上的不足。

<!--more-->

研究背景
--------

传统的社区发现和图划分相关的算法主要采取基于图分割理论、基于模块度优化以及基于标号传播的算法模型。前者主要通过计算网络中的最大流、多层级图分割等方法进行，例如K-L算法，这一算法更倾向于基于数学模型进行相关值的计算，常常得到的结论与网络图的实际结构并不相符。Newman的GN算法是基于模块化优化的社团发现算法的代表，GN算法引入了介数(Betweenness)的概念，通过不断删除介数值大的边来实现图的划分，但这一算法的负责度太高，当节点较多时存在大量的重复计算，因此，在一定程度上并不适用于超大规模社交网络中的社区发现。LPA算法(Label Propagation Algorithm)使用邻居的信息来决定当前节点的社区，但在实际应用中往往存在结果震荡和性能问题。
如今，社交网络体现出内容丰富，信息量大，节点多，随时间演化速度快等特点，在很多真实场景的研究和分析中，传统的社团发现和图划分算法并不适用。引进，引入机器学习中的概率算法模型(如K-means算法)，获取能为这一问题提供一套不错的解决方案。

引入K-means算法的好处
----------------------

将K-means算法引入到社团发现和网络图划分的研究中，在适用性和算法性能等方面存在很多优势。

社团发现和网络图划分问题本质上是一个聚类问题，研究的对象是网络中的个体以及个体间的联系，最终需要通过个体的特性和个体之间的联系的广度和强度来将整个网络划分成几个模块，每个模块具有一个的共性，称为社区。而聚类算法本来就是一相似点为基础，“物以类聚，人以群分”，K-means等聚类算法可以充分利用社交网络中的联系的强弱、频繁程度、甚至是网络中的个体之间交往的内容，结合自然语言处理(NLP)相关领域的知识，可以从更加深入的层次和视角来研究人与人之间的关系，来研究社交网络的划分，来实现真实应用场景下的社团发现。

传统的基于图论、信息论的算法过于注重参数的量化，算法在执行过程中，会进行大量的重复的、冗余的计算，而对于较大规模的真实社交网络，过于细致的量化工作在有些时候甚至出现类似于“过拟合”的现象，使得结果偏离实际。因此，在算法的性能方面，K-means算法同样具有优势。K-means算法迭代速度快，同一，对于在Spark等高性能分布式处理框架上的部署的相关工具和方法都已经非常成熟，使得数据分析工作便于开展。这更加适用于社交网络的动态性等特点，因此，在针对社交网络中的社团发现和图划分算法的研究中，K-means等聚类算法大有可为。

K-means算法
------------

### K-means算法的流程：

已知初始的k个均值点 $ m_1^{(1)},...,m_k^{(1)} $,算法的按照下面两个步骤交替进行：

1. 分配(Assignment)：

将每个观测分配到聚类中，使得组内平方和（WCSS）达到最小。因为这一平方和就是平方后的欧氏距离，所以很直观地把观测分配到离它最近得均值点即可。

$$ S_i^{(t)}=\left \\{ x_p:\left \| x_p-m_i^{(t)} \right \|^2\leq \left \| x_p-m_j^{(t)} \right \|^2\forall j,1\leq j\leq k \right \\} $$

其中每个x_p都只被分配到一个确定的聚类$S^{t}$中。

2. 更新(Update)：

计算得到上步得到聚类中每一聚类观测值的图心，作为新的均值点。
$$ m_i^{(t+1)}=\frac{1}{\left | S_i^{(t)} \right |}\sum_{x_j\in S_i^{(t)}}x_j $$

这一步减小了目标函数组内平方和（WCSS）的值，使得算法收敛。

这一算法将在对于观测的分配不再变化时收敛。由于交替进行的两个步骤都会减小目标函数WCSS的值，并且分配方案只有有限种，所以算法一定会收敛于某一（局部）最优解。

### K-means算法的要点

K-means算法有如下两个比较关键的地方：

1. 如何定义网络中的距离

从算法的描述中，我们不难看出，在K-means算法中，如何定义节点之间的关系非常关键。在前文中我们提到，GN算法引入了介数的概念，通过每次删除图中介数最高的边使得网络图分割成了多个部分，LPA算法通过已知点的信息决定其邻居点，而“邻居”的定义同样需要首先定义节点之间的“距离”。结合社交网络的特性，我认为，有以下三种方法来定义网络图中的“距离”：

(1). 相同邻居数

如今的社交网络足够大、足以表征一个人几乎所有的社会关系，根据三元闭包原则，直接邻居中的共性的大小可以用来表征二者之间的联系的强弱程度。例如，在QQ、微博等社交网络中，共同好友的数量越多，这两人之间的关系越密切，即时二者之间此时没有直接的联系，在未来，在“三元闭包”原则指导下的社区演化也很可能使得这二者之间建立起直接的联系，因此，在大规模社交网络中，这不失为一种定义“距离”的好方法。

(2). 交往的频繁程度

如今，获取个体与个体之间在持续一段时间内的交往次数并不困难，而交往的平凡程度是个体间联系紧密程度的一个很好的体现。例如，在邮件网络中，交往的频繁程度几乎是体现联系紧密程度的唯一因素。同时，这一量化概念易于统计，不会出现过多的“噪声”。

(3). 交往内容的情绪色彩

根据生活常识，我们知道，两个人之间的交往的内容的感情色彩可以很充分地体现出两人之间的联系的强弱，以及联系的演变趋势。现在，针对微博、论坛等的内容的情感分析和自然语言处理技术无论是在效率上还是在质量上相比以往都有了长足的进步，因此我认为，这一方法可以用于度量社交网络中个体间的距离，并进一步作为后续社团发现的研究的基础。

2. 如何选取初始值

K-means算法中初始值选取是否恰当不仅决定着算法的收敛速度，更决定着最终得到的结果的准确性。因此，良好的初始值选择策略是算法成功的关键。针对社团发现这一具体应用场景，可以选取一些在网络中比较重要，即与之相连的边较多的节点来作为初始值，这样的节点更可能是一个社团的中心，因此，这样的初始值更有利于算法的执行。

总结
-----

综上，我们可以大致看到如何将K-means算法应用于社团发现和社交网络图划分算法研究，以及这一方法的优势。与传统的从信息论的观点出发的算法相比，机器学习领域中的概率算法模型在复杂网络的社团发现、多层次网络的分层、大规模网络的图划分等方面有着举足轻重的作用。在近年的KDD等本领域的顶级会议的论文中，已经有学者进行类似的研究并取得了不错的效果。

本文的不足之处在于，由于时间、经历和资源等原因，本文仅仅是做了对一些调研和设想，并未给出K-means算法在真是数据场景下的测试的表现，这也是在后期的课程作业中需要改进的地方。

参考
-----

1. [K-means_clustering](http://en.wikipedia.org/wiki/K-means_clustering)
2. [Community structure in social and biological networks, Girvan M. and Newman M. E. J.](http://www.pnas.org/content/99/12/7821.full.pdf)
3. [k-means Clustering via Principal Component Analysis, Chris Ding and Xiaofeng He](http://ranger.uta.edu/~chqding/papers/KmeansPCA1.pdf)
4. [NP-hardness of Euclidean sum-of-squares clustering, Aloise, D.; Deshpande, A.; Hansen, P.; Popat](http://link.springer.com/article/10.1007%2Fs10994-009-5103-0)
