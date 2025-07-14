# Axioma

Axioma is a desktop application for retrieval-augmented generation (RAG) focused on tackling package dependency hell, a commonly encountered problem in AI-assisted code production. It's achieved through user interaction with the file system-like structure in the backend that clients specify in the GUI. In addition to choosing the specific version of a package, clients are permitted to choose any subset of directories in which there are documents the RAG searches.

## Introduction

Currently I introduce the following features:

- Connection to the custom backend using vector databases
- File-system-like structured view of the database hierarchy
- Selective search over the database from the GUI
- GUI allows OS tools to be used by the response by the LLM-based agent (_mkdir_, _touch_, _ls_ etc.)

I think the last feature where GUI allowing the application to take charge in defining the code environment, possibly creating build scripts itself and running the tests accordingly. Web frontend apps would hit massive security barriers carrying out such file operations, process execution, etc. That's why I chose a desktop app to be the main actuator that executes payloads returned from the server where the agent (specifically ReAct agent) is functioning.

_to be specified further..._

## Structure

Currently, I devised the component diagram as follows.

![Component Diagram for GUI](components.png)

_to be specified further..._
