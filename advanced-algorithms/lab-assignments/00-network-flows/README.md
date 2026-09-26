# Assignment 0: Network Flows

The purpose of this assignment is to gain a basic understanding of solving 
network flow problems via code. 

This is also an assignment that allows you to figure out the basic workflow of 
submitting lab assignments in this course. 

## 0. Setup

### 0.1 GitHub Repository
1. Create a fork of the `advanced-algorithms-2025-01` repository. 
2. Clone your fork (not the main course repo)
3. `cd advanced-algorithms-2025-01` 
4. `git remote add upstream git@github.com:olincollege/advanced-algorithms-2025-01.git`
5. Run `git remote -v` and confirm that `origin` contains your repository and `upstream` contains `olincollege`'s

### 0.2 Prerequisites
Requirements: Python (anaconda or a venv is fine) 3.12

### 0.3 Sync & Branch Your Repo
Make sure that you are at the latest change in your repo by running the following commands:

```
$ git switch main
$ git pull
$ git pull upstream main
$ git push
```

Once you have done this, create a new branch for this assignment:

```
$ git switch -c assignment-00
```

If you are unfamiliar with or have questions about exactly what this is doing,
reach out to the teaching team on Discord, after class, or during office hours.

### 0.4 Assignment-Specific Prerequisites
Run `pip install -r requirements.txt` to acquire all the necessary libraries
used in Assignment 0. 

## 1. Network Flows Lab
The network flows lab assignment can be completed within 
`00-network-flows.ipynb`.

There are two 'parts' to this lab: A & B containing multiple code blocks that
need to be filled out/completed.

## 2. Submission
Before submitting this assignment, make sure that you are on the `assignment-00`
branch. 

Then, `add` and `commit` your changed files. This should only contain the 
notebook edited in part 1. Be sure to write a reasonably clear commit message.

Once you have committed your changes, push them to origin (your fork of the 
course repository). If you have not already established an upstream branch,
you will have to run `git push --set-upstream origin assignment-00`.

Open a pull request, making sure that the base repository is 
USERNAME/advanced-algorithms-20XX-YY. Set 
olincollege/advanced-algorithms-2025-01-instructor as reviewers. 

Submit the URL of the PR in Canvas.

Once again, if you are unfamiliar with this process, or have questions about 
exactly what this is doing, reach out to the teaching team on Discord, 
after class, or during office hours.
