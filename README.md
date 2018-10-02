# YetAnotherGraphPlugin

A plugin for Unreal Engine 4 that allows to create graph-like assets.

<p align="center">
  <img src="https://github.com/LazyTurtle/YetAnotherGraphPlugin/blob/master/docs/images/EditingTheGraph.png">
</p>


## Getting started

- Clone or copy the plugin into the "Plugins" folder of your project. Create one if there is none.
- Generate Visual Studio project files.

### Creating new graphs and nodes

- Create a new Blueprint Graph asset.

<p align="center">
  <img src="https://github.com/LazyTurtle/YetAnotherGraphPlugin/blob/master/docs/images/CreatingTheAssetGraph.png">
</p>

- Create a new blueprint that inherits "SimpleNode" or "StartNode" blueprintable classes.

<p align="center">
  <img src="https://github.com/LazyTurtle/YetAnotherGraphPlugin/blob/master/docs/images/CreatingTheNewAssetNode.png">
</p>

- Customize the new blueprint node. overriding few functions.
- - "InternalGetTitleNode" to change the name displayed int he graph editor.
- - "HasOutpitPins" to remove the bottom area of the node, usually dedicated to the output pins.
- - "HasInputPins" to remove the upper area of the node, usually dedicated to the input pins.
- - Add any kind of new variable that you wish.

<p align="center">
  <img src="https://github.com/LazyTurtle/YetAnotherGraphPlugin/blob/master/docs/images/CustomizingTheNewNode.png">
</p>

- Spawn the node in the graph editor.

<p align="center">
  <img src="https://github.com/LazyTurtle/YetAnotherGraphPlugin/blob/master/docs/images/SelectingTheNode.png">
</p>

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
