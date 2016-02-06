=======
Caravan
=======

Caravan is the start of a decentralized package manager for C based languages. If a project can be built via the command line into shared or dynamic library, then it can be used with caravan.

How It Works
============

1. Create a Caravan file listing your dependencies
2. Run the ``caravan`` utility to install and build your dependencies
3. Use ``caravan`` to list headers and linked dependencies in order to build/link your app.


Caravan Files
=============


Caravan files are a simple DSL for defining your projects dependencies::

    Statements    ::= Statement OptionalStatements
    OptionalStatements ::= Statements | λ
    Statement     ::= RepoType RepoURL Version OptionalSpec
    RepoType      ::= 'git'
    RepoURL       ::= String
    Version       ::= GitRef | VersionPrefix SemVer
    GitRef        ::= String # any valid git reference
    VersionPrefix ::= '^' | '>' | '>='
    SemVer        ::= Major '.' Minor OptionalPatch
    Major         ::= Int
    Minor         ::= Int | '*'
    OptionalPatch ::= '.' Minor | λ
    Int           ::= [0-9]
    String        ::= '"' (\\.|[^\\"])* '"'
    OptionalSpec  ::= '{' SpecStatements '}' | λ


For any projects that want to simplify Caravan builds of themselves, they can add a .caravan-spec file ::

    SpecStatements      ::= Statement OptionalStatements
    OptionalStatements  ::= Statements | λ
    Statement           ::= BuildDefinition CommandStatement
    BuildDefinition     ::= 'static-lib' Libdir Libname | 'include' Includedir
    Libdir              ::= String
    Libname             ::= String
    Includedir          ::= String
    CommandStatement    ::= '{' Commands '}'
    Commands            ::= Command OptionalCommands
    Command             ::= [^Separator]*
    OptionalCommands    ::= Separator Commands | λ
    Separator           ::= \n(\s+)
    String              ::= '"' (\\.|[^\\"])* '"'

Example Caravan File ::

    git "git@github.com:repo/project.git" ^0.1
    git "/Users/username/project" "master" {
        static-lib "lib" "name" {
            make libname
        }
        include "include" {
            INCLUDE_DIR=include make install
        }
    }

Example Spec ::

    static-lib "libraries" "git2" {
        make git2
        mv build/libgit2.a libraries
    }
    include "inc" {

    }


Module Task List
================

:Parse:
    Parses the Caravan file and .caravan-spec and builds AST, handles AST Validation
:Resolve:
    Broken into three steps: Fetch, Resolve,
    Goes through AST and fetches all repositories per VCS. Resolves the version and/or ref into an actual version or ref for the repo. Stores the resolved versions in a file for caching and versioning in order to prevent doing this resolve step again.
:Build:
    Builds the resouces for each individual dependency. This will also recursively start the process again for any sub dependency that lists a Caravan file. After all of the building, caravan will create a resources file which is cached version of all the resources that caravan uses for helping with the build
:Resource:
    Once the project's dependencies have been built and a resource file exists for letting Caravan know of all the resources that were built. The caravan will then be used by the project to help display any resource specific data. E.g. for c specific resources, the resouce command will output all lib and include flags used for a standard C compiler.
