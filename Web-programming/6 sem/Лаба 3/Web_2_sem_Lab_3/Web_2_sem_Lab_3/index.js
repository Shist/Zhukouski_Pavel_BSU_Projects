// --------------- PAGE ROOT
let root = document.querySelector('.page');
// --------------- READER TABLE
let readers = [
    [1, 'Sasha', '2000-08-14'],
    [2, 'Artem', '2000-02-11'],
    [3, 'Polina', '1999-08-26'],
    [4, 'Masha', '1998-03-25'],
    [5, 'Andrey', '1978-07-26']
]
let readerHead = ['ID', 'Name', 'Burth Date'];
let readerQuestion = "Readers";

// --------------- BOOK TABLE
let books = [
    [1, 'Harry Potter', 'J.K.Rowling', '3'],
    [2, 'Winnie-the-Pooh', 'Alan Alexander Milne', '2'],
    [3, 'Jeeves and Wooster stories', 'P.G.Wodehouse', '5'],
    [4, 'Harry Potter and the Philosopher’s Stone', 'J.K.Rowling', '10'],
    [5, 'Airport', 'Arthur Hailey', '2']
]
let bookHead = ['ID', 'Name', 'Author', 'Number of Instances'];
let bookQuestion = "Books";

// --------------- FORMULAR TABLE
let formular = [];
let formularHead = ['Book id', 'Reader id', 'Start date', 'End date', 'Return date'];

// --------------- DEBTORS TABLE
let debtors = [];
let debtorHead = ['Reader id', 'Book id', 'Days'];

// --------------- NUMBER OF INSTANCE TABLE
let getNumberOfInstHead = ['Book id', 'Number of Instances'];

// --------------- FORM INFORMATION
let getBookByAuthorForm = [
    ['input', 'text', 40, 'author', 'authorName', 'Author\'s name'],
    ['button', 'button', 'OK', 'buttonID', 'getBookByAuthor()']
]
let getNumberOfInstanceForm = [
    ['input', 'text', 40, 'book', 'bookID', 'Book\'s id'],
    ['button', 'button', 'OK', 'buttonID', 'getNumberOfInstance()']
]
let getBookForm = [
    ['input', 'text', 40, 'book', 'bookID', 'Book\'s id'],
    ['input', 'text', 40, 'reader', 'readerID', 'Reader\'s id'],
    ['button', 'button', 'Take', 'buttonTakeID', 'takeBook()'],
    ['input', 'text', 40, 'reader', 'yourID', 'Your id'],
    ['input', 'text', 40, 'reader', 'bookToReturnID', 'Book\'s id'],
    ['button', 'button', 'Return', 'buttonReturnID', 'returnBook()'],
    ['button', 'button', 'Debtors', 'buttonDebtorsID', 'getDebtors()'],
]

// --------------- MAIN PAGE EVENT
function showAllReaders(){
    window.open("showAllReaders.html");
}

function showAllBooks(){
    window.open("showAllBooks.html");
}

function bookByAuthor(){
    window.open("getBookByAuthorPage.html");
}

function getNumberOfInst(){
    window.open("getNumberOfInsttance.html");
}

function getReturnDebtors(){
    window.open("getBook.html");
}

// --------------- GENERATE TABLES
function generateTable(root, headerValue, tableHead, elementsArray){
    var header = document.createElement('h3');
    header.innerHTML = headerValue;
    root.append(header);
    var tableTag = document.createElement('table');
    root.append(tableTag);
    var tableHeader = document.createElement('tr');
    var tableHeaderColumn;
    var row;
    tableTag.append(tableHeader);
    for(let i = 0; i < tableHead.length; i++){
        tableHeaderColumn = document.createElement('th');
        tableHeaderColumn.innerHTML = tableHead[i];
        tableHeader.append(tableHeaderColumn);
    }
    for(let i = 0; i < elementsArray.length; i++){
        row = document.createElement('tr');
        tableTag.append(row);
        for(let j = 0; j < elementsArray[i].length; j++){
            var elements = document.createElement('td');
            elements.innerHTML = elementsArray[i][j];
            row.append(elements);
        }
    }
}

// --------------- GENERATE FORMS
function generateForm(formArray){
    var form = document.querySelector('form');
    for(let i = 0; i < formArray.length; i++){
        if(formArray[i][0] == 'input'){
                let input = document.createElement(formArray[i][0]);
                input.setAttribute("type", formArray[i][1]);
                input.setAttribute("size", formArray[i][2]);
                input.setAttribute("name", formArray[i][3]);
                input.setAttribute("id", formArray[i][4]);
                input.setAttribute("placeholder", formArray[i][5])
                form.append(input);
        }
        else if(formArray[i][0] == 'button'){
                let button = document.createElement(formArray[i][0]);
                button.setAttribute("type", formArray[i][1]);
                button.setAttribute("id", formArray[i][3]);
                button.setAttribute("onclick", formArray[i][4]);
                button.innerHTML = formArray[i][2];
                form.append(button);
        }
    }
}

// --------------- FUNCTIONS
// --------------- get book by author name
function getBookByAuthor(){
    let root = document.querySelector('.result');
    let input = document.getElementById('authorName').value;
    let newBooks = [];
    for(let i = 0; i < books.length; i++){
        if(books[i][2] == input){
            newBooks.push(books[i]);
        }
    }
    if(newBooks.length > 0){
        var string = input + "s' books";
        generateTable(root, string, bookHead, newBooks);
    }
    else{
        alert("No book by this author")
    }
}
// --------------- get number of inctanse of book by id
function getNumberOfInstance(){
    let root = document.querySelector('.result');
    let input = document.getElementById('bookID').value;
    let elements = [];
    for(let i = 0; i < books.length; i++){
        if(books[i][0] == input){
            let element = [input, books[i][3]];
            elements.push(element);
        }
    }
    generateTable(root, "Books' number of instance", getNumberOfInstHead, elements);
}
// --------------- take book by id
function takeBook(){
    let root = document.querySelector('.result');
    let bookID = document.getElementById('bookID').value;
    let readerID = document.getElementById('readerID').value;
    var startDate = new Date();
    var endDate = new Date();
    endDate.setMonth(startDate.getMonth() + 3);
    var element = [bookID, readerID, dateFormat(startDate), dateFormat(endDate), ''];
    formular.push(element);
    generateTable(root, "Formular", formularHead, formular);
}
// --------------- return book by id
function returnBook(){
    let yourID = document.getElementById('yourID').value;
    let bookToReturnID = document.getElementById('bookToReturnID').value;
    for(let i = 0; i < formular.length; i++){
        if(formular[i][1] == yourID){
            if(formular[i][0] == bookToReturnID){
                formular[i][4] = dateFormat(new Date().setMonth(new Date().getMonth()+7));
                generateTable(root, "Formular", formularHead, formular);
            }
            else{
                alert("You did not take book with this ID.")
            }
        }
        else{
            alert("You did not take any book.")
        }
    }
}
// --------------- get debtors
function getDebtors(){
    for(let i = 0; i < formular.length; i++){
        let startDate = new Date(formular[i][2]);
        let endDate = new Date(formular[i][3]);
        console.log(endDate)
        let returnDate = new Date(formular[i][4]);
        let period = Math.ceil(Math.abs(returnDate.getTime() - endDate.getTime()) / (1000 * 3600 * 24));;
        console.log(period)
        if(period >= 60){
            let debtor = [formular[i][1], formular[i][0], period]
            debtors.push(debtor);
            generateTable(root, "Debtors", debtorHead, debtors);
        }
    }
}
// --------------- to format date
function dateFormat(d){
    const ye = new Intl.DateTimeFormat('en', { year: 'numeric' }).format(d)
    const mo = new Intl.DateTimeFormat('en', { month: 'short' }).format(d)
    const da = new Intl.DateTimeFormat('en', { day: '2-digit' }).format(d)
    return [ye+'-'+mo+'-'+da];
}