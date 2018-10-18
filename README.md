# YetAnotherGraphPlugin
### Making graphs effortless.

A plugin for Unreal Engine 4 that allows to create graph-like assets.

<p align="center">
  <img src="https://github.com/LazyTurtle/YetAnotherGraphPlugin/blob/master/docs/images/EditingTheGraph.png">
</p>


## Getting started

- Clone or copy the plugin into the "Plugins" folder of your project. Create one if there is none.
- Generate Visual Studio project files.

## Native Features

### Naming Nodes
Is now possible to name nodes. Named nodes can be accessed directly using the `NamedNodes` property of the graph asset
<p align="Center">
  <img src="https://github.com/LazyTurtle/YetAnotherGraphPlugin/blob/master/docs/images/RenamingNode.png">
  <img src="https://github.com/LazyTurtle/YetAnotherGraphPlugin/blob/master/docs/images/NamedNodes.png">
</p>

### Native Nodes
The Plugin comes with 6 different nodes for basic graph creations. They are divided into 3 groups:

* Empty Nodes: This nodes don't have any property and are to be used as parent class of the nodes that will store the informations.
<p align="center">
  <img src="https://github.com/LazyTurtle/YetAnotherGraphPlugin/blob/master/docs/images/EmptyNodes.png">
</p>

* Action Nodes: This are transparent nodes. In other words they aren't visible when navigating the graph using the function `GetChildren` of a node and at their place there will be their subnode. Before returning the subnode they perform a blueprintable function. With the plugin there are 2 implementation that store a named variable and its value on the external `UObject` owner of the graph that __must__ implement the `YetAnotherGraphInterface` interface (for exchanging informations between graphs and objects). If there isn't just a single subnode (there are 0 or more then 1 subnodes) the node will not perform the action and will not return its subnode. The two implementation are:

  * `Store Boolean`: stores a named boolean variable
  * `Store Integer`: stores a named integer.
  
<p align="Center">
  <img src="https://github.com/LazyTurtle/YetAnotherGraphPlugin/blob/master/docs/images/StoreBooleanNode.png">
  <img src="https://github.com/LazyTurtle/YetAnotherGraphPlugin/blob/master/docs/images/StoreIntegerNode.png">
</p>

* Flow Control: The task of this nodes is to change dinamically the node they return when navigating the graph. Much like the action nodes they're completely transparent when using the graph. When using the function `GetChildren` on any node if among those subnodes there is a Flow Control node it will not be seen. Instead, in place of the flow control node, there will be one of its subnodes, depending on the specific result of the evaluation implemented. There are 2 flow control abstract classes you can inherit: `BinarySelector` and `MultiNodeSelector`. But there are 2 implementations that take advantage of the action nodes:

  * `Boolean Selector` will look up the boolean value associated with the variable name and that returns one of at most two nodes. On true it will return the node on the left. If there are 0 or more than 2 nodes or the evaluation turns out to be false on a single subnode, it will not return anything.

  * `Nth Selector` will look up the integer associated with the variable name and return the nth-subnode, counting them from left to right and starting from 0. If there are 0 nodes or the evaluation calculate an index outside the number of nodes, it will not return anything.
  
<p align="Center">
  <img src="https://github.com/LazyTurtle/YetAnotherGraphPlugin/blob/master/docs/images/BooleanSelector.png">
  <img src="https://github.com/LazyTurtle/YetAnotherGraphPlugin/blob/master/docs/images/NthSelectorNode.png">
</p>

If a flow control node doesn't return any node, it won't appear among the children of the node that called the function.
If needed it's still possible to have a reference of this nodes. They are present in the 'Nodes' property of the graph asset, and they can be named and referenced directly using the `NamedNodes` map property.

### Creating new graphs and nodes

- Create a new Blueprint Graph asset.

<p align="center">
  <img src="https://github.com/LazyTurtle/YetAnotherGraphPlugin/blob/master/docs/images/CreatingTheAssetGraph.png">
</p>

- Create a new blueprint that inherits `SimpleNode` or `StartNode` blueprintable classes.

<p align="center">
  <img src="https://github.com/LazyTurtle/YetAnotherGraphPlugin/blob/master/docs/images/CreatingTheNewAssetNode.png">
</p>

- Customize the new blueprint node. overriding few functions.
  - `GetTitleNode` to change the name displayed int he graph editor.
  - `HasOutpitPins` to remove the bottom area of the node, usually dedicated to the output pins.
  - `HasInputPins` to remove the upper area of the node, usually dedicated to the input pins.
  - Add any kind of new variable that you wish.

<p align="center">
  <img src="https://github.com/LazyTurtle/YetAnotherGraphPlugin/blob/master/docs/images/CustomizingTheNewNode.png">
</p>

  - Add your categories separated by a `|` for creating your own list on the graph

<p align="Center">
  <img src="https://github.com/LazyTurtle/YetAnotherGraphPlugin/blob/master/docs/images/NodeCategory.png">
  <img src="https://github.com/LazyTurtle/YetAnotherGraphPlugin/blob/master/docs/images/Categories.png">
</p>

- Spawn the node in the graph editor by dragging an arrow from its parent or by right clicking on the graph editor.


This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
