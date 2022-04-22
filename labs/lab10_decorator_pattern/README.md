# Lab 10 Decorator Design Pattern Lab
_(Due **Thursday**, April 7, 2022 @ 11:59pm)_

## Introduction

This lab will introduce you to a decorator design pattern that is used frequently in software design. <br>
In previous labs, we have finally managed to move the entities from one place to another. For this lab, we are going to make the entity celebrate once they get to their final destination by spinning around using the decorator design pattern.

## Retrieve Class Materials

Navigate to your repository.

```bash
% cd <path_to_directory_repo-userid>
```
**Make sure** that you are inside the main branch.
Run the following command and see which branch you are in.
```bash
% git branch
```
If you see the following (asterisk symbol in front of some other branch instead of "main"), then you would need to switch to the main branch, otherwise skip this step. The asterisk * symbol indicates the branch you are in.
```bash
* lab08
  main
```
To switch to the main branch, run the following command. The keyword **checkout** indicates we want to switch to the specified and existing branch.
```bash
% git checkout main
```

Pull the latest changes from the repository.

```bash
% git pull
```

Check the list of all the Git branches in this repository. Initially, a Git repository has only one branch called `main`. For this lab, we have created a new branch. A branch is a separate identical copy of the repository. This allows you to make changes on this new branch without messing with the original `main` branch.

```bash
% git branch -a
```

You'll notice that there is a new `lab10` branch along with other branches such as lab07. You can go ahead and switch over to the branch called 'lab10'.<br>

```bash
% git checkout lab10
```

## Where to work?

Go to the `project` folder at the root folder instead of the lab10 folder. You will be working and modifying the code inside this folder rather than the `labs` folder. The individual lab folders will be provided to give instructions on what to do, such as the current lab10 folder. 

```bash
% <make_sure_you_are_inside_the_root_folder(directory_repo)>
```

Make sure you are in the correct branch by running the command below. If you see ***lab10**, then you are inside the correct branch. Else, go back to the instructions provided at the beginning.
```bash
% git branch
```

Go to the project base code folder
```bash
% cd project
```
You will be working inside this folder.

## How to run the project?

If you attended workshop 3, I bet you already know how to run the code. However, for those who either don't know or forgot how to run it, the following commands will show you how to run the visualization.

````bash
# Locate to the project base code folder first.
# Clean the project
% make clean

# Build the project
% make -j

# Run the project (./build/web-app <port> <web folder>)
% ./build/bin/transit_service 8081 apps/transit_service/web/
````
Navigate to http://127.0.0.1:8081 and you should see a visualization. <br>
Navigate to http://127.0.0.1:8081/schedule.html and you should see a a page to schedule the trips.
To view the entities, click on the right top of the visualization page (not the schedule page) and choose the entity to view such as drone or (robot name) that you give in the schedule page.


## The Decorator Pattern

The Decorator Pattern is used for adding more behaviors/functionality to an object at runtime.

<p align="center"> <img src="patternPics/decoratorPatternExample.png" alt="decorator example uml" class="shadow" style="height:700px;width:auto;border-radius:5px;1"></p>

A great example of the decorator pattern is a pizza toppings. In this analogy the pizza base is first created and the toppings were added later onto it. Everytime the toppings were added, the price of the pizza increases depending on the toppings. The toppings can add not only to the pizza but also other type of food if it exists as well.

## Drone and Robot celebration decorator pattern

<p align="center"> <img src="patternPics/projectDecoratorPattern.png" alt="github issues" class="shadow" style="height:700px;width:auto;border-radius:5px;1"></p>

*Note: This UML is the addition of the UML that we used for Strategy Pattern*<br>

The entities will celebrate once they get to their destination by spinning around. We will implement this by using decorator pattern. For this lab, we will only have spinning around as celebration, however you can be creative and add more additional celebration style as you wish (just let the TA know that you are implementing additional celebration style once you submit).

# What to do?
For this lab, you will be adding new code to the project to implement and use the **Decorator Design pattern** that you have seen above.

- Create CelebrationDecorator class and SpinDecorator class where these classes will be used to spin the entities once they get to their destination.
- The decorator class will only be applied to the movement that uses AStar, DFS, and Dijkstra strategy. This decorator should **NOT** apply if the beeline is used. 
- The spinTime should be set to 0 initially, and the entities should rotate upto maximum spintim = 1.5. (So, the max time for which the entity spins = 1.5)
- The SpinDecorator will check whether the movement strategy is completed or not and if it is completed, it will start to spin. You can spin the entity by calling the rotate function inside the entity, if you want to increase the speed of spinning, you would need to increase the parameter that is being passed into the rotate function.

**Hint**: *Use the UML diagram provided for strategy design pattern to get started.*

Finally, you will have the following new files in your project folder:
- CelebrationDecorator.cc/.h
- SpinDecorator.cc/.h
- drone.cc (Modified)

After you completed implementing the strategy design pattern, your drone and robot should spin around once they reach their destination (excluding the beeline).

# Submission
Show your section TAs your final result and get checkedoff for this lab.

_(Due **Thursday**, April 7, 2022 @ 11:59pm)_
