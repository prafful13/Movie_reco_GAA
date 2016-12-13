# Movie Recommender System using Genetic Algorithm Approach

In this project i have tried to implement the following research paper published by Jesus Bobadilla, Fernando Ortega, Antonio Hernando and Javier Alcalá of Universidad Politécnica de Madrid, Computer Science, Crta. De Valencia, Km 7, 28031 Madrid, Spain.
</br>
</br>
Their research paper titled: 'Improving collaborative filtering recommender system results and performance using genetic algorithms' can be found at: http://www.sciencedirect.com/science/article/pii/S0950705111001146
</br>
</br>
This project contains the following files:</br>
1) main.cpp which has all the algorithms implemented</br>
2) userdatageneration.cpp which is used to develop random data of users</br>
3) movie.txt which contains our database on movies</br>
</br>
</br>
The algorithm works by collecting the data of other users (ratings in our case) and recommend the logged in user by comparing the similarity between them, hence collaborative. We have used GA (for 30 generations) to find the best weight vector to give better recommendations to the users.
