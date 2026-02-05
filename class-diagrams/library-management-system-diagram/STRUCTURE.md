# Library Management System Class Diagram - Structure Overview

## Summary

This folder contains a complete recreation of the Library Management System class diagram based on the Python implementation. The diagram includes all classes, interfaces, enumerations, and relationships from the original design.

## Files Created

1. **library_management_system.puml** - PlantUML source file (primary format)
2. **library_management_system.mmd** - Mermaid format (alternative for easier viewing)
3. **README.md** - Instructions on how to generate PNG images
4. **generate_diagram.py** - Python script to automatically generate PNG
5. **STRUCTURE.md** - This file (overview of the structure)

## Class Diagram Components

### Enumerations (1)
- **ItemType**: BOOK, MAGAZINE

### Interfaces (2)
- **ItemState**: Defines checkout, returnItem, and placeHold operations
- **SearchStrategy**: Defines search operation

### Abstract Classes (1)
- **LibraryItem**: Base class for library items with observer pattern support

### Concrete Classes (12)

#### Item Types
- **Book**: Extends LibraryItem, has author attribute
- **Magazine**: Extends LibraryItem, has publisher attribute

#### State Pattern (3)
- **AvailableState**: Item is available for checkout
- **CheckedOutState**: Item is currently checked out
- **OnHoldState**: Item is on hold for a member

#### Strategy Pattern (2)
- **SearchByTitleStrategy**: Searches items by title
- **SearchByAuthorStrategy**: Searches items by author/publisher

#### Core Classes (6)
- **LibraryManagementSystem**: Singleton managing catalog, members, and copies
- **BookCopy**: Represents a physical copy of an item with state
- **ItemFactory**: Factory for creating LibraryItem instances
- **Member**: Library member with loans and observer capability
- **Loan**: Represents a checkout transaction
- **TransactionService**: Singleton managing active loans
- **LibraryManagementDemo**: Entry point/demo class

## Design Patterns Implemented

1. **Singleton Pattern**: 
   - LibraryManagementSystem
   - TransactionService

2. **State Pattern**: 
   - ItemState interface with AvailableState, CheckedOutState, OnHoldState implementations

3. **Strategy Pattern**: 
   - SearchStrategy interface with SearchByTitleStrategy and SearchByAuthorStrategy

4. **Factory Pattern**: 
   - ItemFactory for creating different item types

5. **Observer Pattern**: 
   - LibraryItem as Subject, Member as Observer

## Relationships

### Inheritance
- LibraryItem → Book, Magazine
- ItemState → AvailableState, CheckedOutState, OnHoldState
- SearchStrategy → SearchByTitleStrategy, SearchByAuthorStrategy

### Composition (Strong ownership)
- LibraryItem *-- BookCopy (LibraryItem owns BookCopy instances)
- BookCopy *-- ItemState (BookCopy owns its current state)
- Member *-- Loan (Member owns Loan instances)

### Association
- LibraryManagementSystem manages BookCopy, LibraryItem, Member
- BookCopy references LibraryItem
- LibraryItem has Member observers
- Loan references BookCopy and Member
- TransactionService manages Loan instances

### Dependency
- LibraryManagementDemo uses LibraryManagementSystem
- LibraryManagementSystem uses ItemFactory, SearchStrategy, TransactionService
- ItemFactory uses ItemType and creates LibraryItem
- Member observes LibraryItem

## Verification

The diagram has been verified to match the original structure including:
- ✓ All classes and their attributes
- ✓ All methods with correct signatures
- ✓ All relationships (inheritance, composition, association, dependency)
- ✓ All design patterns correctly represented
- ✓ Singleton pattern markings
- ✓ Interface implementations
- ✓ Enumeration types

## Next Steps

To generate the PNG image:

1. **Quick option**: Use the online PlantUML server
   - Copy contents of `library_management_system.puml`
   - Visit: http://www.plantuml.com/plantuml/uml/
   - Paste and download

2. **Mermaid option**: Use any Mermaid viewer
   - Copy contents of `library_management_system.mmd`
   - Use VS Code Mermaid extension or online viewer

3. **Command line**: Install PlantUML and Graphviz
   - Run: `plantuml -tpng library_management_system.puml`

