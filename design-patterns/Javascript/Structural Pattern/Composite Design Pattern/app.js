const File = require("./file");
const Folder = require("./folder");

// Let's create some files with random file extensions
const file1 = new File("File1.js");
const file2 = new File("File2.py");
const file3 = new File("File3.cpp");
const file4 = new File("File4.txt");
const file5 = new File("File5.docx");
const file6 = new File("File6.xlsx");
const file7 = new File("File7.pptx");
const file8 = new File("File8.pdf");
const file9 = new File("File9.png");
const file10 = new File("File10.jpg");

// Let's create a folder to add files
const folder1 = new Folder("Folder1");
folder1.add(file1);
folder1.add(file2);
folder1.add(file4);

const folder2 = new Folder("Folder2");
folder2.add(file3);
folder2.add(file8);

const folder3 = new Folder("Folder3");
folder3.add(file5);
folder3.add(file9);
folder3.add(file10);

const folder4 = new Folder("Folder4");
folder4.add(file6);
folder4.add(file7);

// Let's create a root folder
const rootFolder = new Folder("Root");
rootFolder.add(folder1);
rootFolder.add(folder2);
rootFolder.add(folder3);
rootFolder.add(folder4);


// Let's show the details from the root folder
rootFolder.showDetails();
