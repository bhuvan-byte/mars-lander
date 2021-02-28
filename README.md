# mars-lander

An attempt to solve mars lander through genetic algorithm and sine and cosine sum series (i.e. a<sub>n</sub>(sin(nx)+b<sub>n</sub>(cos(nx))) \
The challenge is inspired by a puzzle on condingame <https://www.codingame.com/ide/puzzle/mars-lander-episode-3> </br>

The algorithm uses a set of randomly chosen parameters as coefficients to the sine cosine sum series.

The generated function is then used to output the "power" and the "angle" for the lander.
Several such sets of parameters are selected and the best ones are kept while discarding the bad choices. Then answer is improved upon by  procedure similar to that of genetic algorithm.
</br>

![Different Paths explored while running genetic algorithm](readme_asset/path.gif)
</br>
In working on the codingame site mentioned above
![The simulation running on the platform of the codingame site](readme_asset/mars.gif)
