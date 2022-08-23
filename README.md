# GameVersion
Unreal Engine Plugin with utilities for project versioning, package versioning, and build numbers

<sub>(This plugin is in an early development stage and will receive updates and changes ad hoc)</sub>

### Features
This plugin allows developers to fetch the latest build information for their game from a static version service endpoint that hosts a JSON file containing such information. <br>
This plugin will parse that information, populate custom data types, and allow developers to compare the current version of the client build to the latest one and determine what user-facing action needs to happen. 
This plugin also contains the necessary utilities to assign version numbers and other information of that sort to builds of a project and make integration with CI/CD systems easier.

### Usage
You should be able to drop this plugin right into your project's ```"Plugins"``` folder, compile, and have it work. I will most likely include precompiled binary releases some time in the near future.





