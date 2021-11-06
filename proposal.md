## CS 225 Data Structures

## Group Proposal

## Idea

Use steam game text description and tags to recommend similar games.
Network of similar games based on tags, descriptions, genres…
What games are on sale
What games are highest rated for their category
Basically a worse steam client.

## IMPORTANT
At least one team member should research and familiarize themselves with some GUI system so we can hit the ground running when we start implementing our algorithms. (Visual feedback is noice!)
## Resources
Force Directed Graph Algorithm
http://cs.brown.edu/people/rtamassi/gdhandbook/chapters/force-directed.pdf

## Steam
https://steamdb.info/
https://steamcommunity.com/dev Steam’s official API
https://www.kaggle.com/trolukovich/steam-games-complete-dataset (this one has like 40k games with game descriptions)

## Leading Questions
What do we want to do? 
We want to use the steam data set and we will make a graph where all the nodes are unique games. There will be an edge between nodes if the two games are similar enough to each other. Deciding whether games are “similar enough” can be implemented using a TF-IDF score or similar term frequency score of the tags and/or descriptions of the individual games. If the scores are similar enough within a tolerance then there will be a node between them. We can also use a machine learning algorithm to recommend (draw an edge to another) game/node based on the current game/node.
Implement a GUI to inspect the graph and find similar games. We could have a user input for a certain game then it will output similar games for the user to play.

## What is a successful project?
	An app capable of exploring related games from Steam graphically, through organization of similar tags, descriptions and (possibly) ratings.
Dataset Acquisition and Processing
At least one public dataset.
Using either https://www.kaggle.com/trolukovich/steam-games-complete-dataset or https://steamcommunity.com/dev
Describe how to acquire, store, and process data. 
We can use python (pandas) to clean and combine all the data into a csv file or similar format
Describe format and how it will be used in graph structures.
Each node will be an individual game and 2 nodes will have an edge between them if they are “similar”
Describe how to deal with errors.
Data portions with items missing or which have been identified to be wrong will be removed from the set.

## Graph Algorithms
At least two graph data algorithms and a graph traversal from the list of example goals, OR equivalent work.
BFS - documentation, possible alt implementations and complexity
Strongly (or almost) connected components - documentation, possible alt implementations and complexity
Force Directed Graphing - documentation, possible alt implementations and complexity
Documentation for each method, including alternative implementations, time and space complexity.
https://docs.google.com/document/d/10VL05FxUCQZMLb_jQfsfOMNR56ecxy0aIaqPH6KumBQ/edit?usp=sharing


## Timeline 
Identify a list of tasks ( data acquisition, data processing, individual algorithm completion, final deliverable production
Make a timeline using the above. 
Tentative thoughts
	Data acquistion/processing-
	Algorithms and functionality-
		BFS-
		Strongly Connected Components-
		Force Directed Graphing-
		GUI learn/creation-
	Final deliverable completion date-


## Discarded
Predict Covid rates geographically.

Economic impact of Covid on certain regions.

Radiation levels post-nuclear disasters

https://splunk-public.machinedata.illinois.edu/en-US/app/uofi_shield_public_APP/home

https://piktochart.com/blog/100-data-sets/

https://www.kaggle.com/connorwynkoop/steam-monthly-player-data

https://www.kaggle.com/unsdsn/world-happiness
