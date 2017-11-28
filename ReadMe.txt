5.) For my neural network I created a class that would design and populate a network. Nodes are then
			generated and connected throughout the layers of this network. There is an input layer,
			an output layer, and several hidden layers in between them. These layers and their nodes
			are connected to each other by a random weight.
			
		I normalized the data for each csv file. I did this because originally I was going to try and
			create a method that would try and normalize given data in any file, but the task proved to
			be too large for this project. So I instead went in and created a loop that would assign a 
			value between 0 and 1. 
			
		I had to add a comma to the end of each line in the csv so that the last string was added to
			my array.