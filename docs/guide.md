---
layout: default
title: Vombat guide
---

**Basics of Vombat**

Vombat is a toolbar for CloudCompare that looks more or less like this one  (might change depending on the specific revision):

<div style="text-align:center"><img src ="pics/toolbar.svg" width="400" /></div>

each icon represent a specific function of the plugin. 
Basic knowledge of CloudCompare (CC) is required, given the plugin works in a similar manner. You select any object in the DBTree window of CC and the available tools for that specific selection will be colored. Unavailable tools are instead grayed out.

Each tool perform a specific operation on the selected object. Some of them, once activated, will present a further dialog, in which the options can be configured.


**Tools**
Here is a description of the tools implemented in Vombat

*Attitude Fitting*
<img style="float: left;"  src ="https://raw.githubusercontent.com/luca-penasa/vombat/master/icons/attitude.png" width="35" />



The tool compute the best fitting attitude for any selected set of points. When multiple sets of points are selected Vombat will output a new Attitude object for each selected point cloud. Optionally it allows to compute a _fixed normal_ attitude for all the selected point clouds.

This is useful when computing multiple attitudes which must have the same orientation in space, although they are located in different parts of the outcrop, e.g. plane parallel stratification or sets of joints