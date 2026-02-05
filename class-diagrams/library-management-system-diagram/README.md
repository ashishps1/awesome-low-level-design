# Library Management System - Class Diagram

This folder contains the PlantUML class diagram for the Library Management System.

## Files

- `library_management_system.puml` - PlantUML source file containing the complete class diagram definition

## How to Generate PNG Image

### Option 1: Using PlantUML Command Line Tool

1. Install PlantUML:
   - Download from: http://plantuml.com/download
   - Or install via package manager:
     - **MacOS**: `brew install plantuml`
     - **Linux**: `sudo apt-get install plantuml`
     - **Windows**: Download JAR file from PlantUML website

2. Install Graphviz (required for PlantUML):
   - **MacOS**: `brew install graphviz`
   - **Linux**: `sudo apt-get install graphviz`
   - **Windows**: Download from https://graphviz.org/download/

3. Generate PNG:
   ```bash
   plantuml -tpng library_management_system.puml
   ```

### Option 2: Using Online PlantUML Server

1. Open the `library_management_system.puml` file
2. Copy its contents
3. Visit: http://www.plantuml.com/plantuml/uml/
4. Paste the content
5. Download the generated PNG image

### Option 3: Using VS Code Extension

1. Install "PlantUML" extension in VS Code
2. Open the `.puml` file
3. Press `Alt + D` (or `Cmd + D` on Mac) to preview
4. Right-click and export as PNG

### Option 4: Using Python Script

Run the provided Python script:
```bash
python generate_diagram.py
```

(Note: Requires `plantuml` package: `pip install plantuml`)

## Diagram Structure

The class diagram includes:

- **Enumerations**: `ItemType`
- **Interfaces**: `ItemState`, `SearchStrategy`
- **Abstract Classes**: `LibraryItem`
- **Concrete Classes**: 
  - `Book`, `Magazine` (Item types)
  - `AvailableState`, `CheckedOutState`, `OnHoldState` (State pattern)
  - `SearchByTitleStrategy`, `SearchByAuthorStrategy` (Strategy pattern)
  - `LibraryManagementSystem`, `BookCopy`, `ItemFactory`, `Member`, `Loan`, `TransactionService`
- **Design Patterns**:
  - Singleton (LibraryManagementSystem, TransactionService)
  - State Pattern (ItemState implementations)
  - Strategy Pattern (SearchStrategy implementations)
  - Factory Pattern (ItemFactory)
  - Observer Pattern (LibraryItem ↔ Member)

## Relationships

- **Inheritance**: LibraryItem → Book/Magazine, ItemState → State classes, SearchStrategy → Strategy classes
- **Composition**: LibraryItem *-- BookCopy, BookCopy *-- ItemState, Member *-- Loan
- **Association**: Various class relationships
- **Dependency**: Usage relationships between classes

