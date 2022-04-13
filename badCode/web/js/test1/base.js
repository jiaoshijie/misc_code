// var let const

if (false)
{
  const name = ['jiao', 'shi', 'jie'];

  let age = 20;

  for (let i = 0; i < 10; i++)
  {
    let age = 10;
    console.log(name[i], age);
  }

  console.log('This is a Array [' + name + '] and I am ' + age)
}

// String Numbers Boolean null undefined Symbol

if (false)
{
  // String
  let string = "This is a String type.";
  console.log(`content is ${string}, and type is ${typeof string}`);

  // Numbers
  let int = 20;
  let PI = 3.1415926;
  let l = -10;

  let sum = int + PI;

  console.log(`sum is ${sum}, and type is ${typeof sum}\n int is ${20}, and type is ${typeof int}\n l is ${l}, and type is ${typeof l}\n PI is ${PI}, and type if ${typeof PI}`);

  // Boolean
  let isempty = true;
  let isfull = false;

  if (isempty)
  {
    console.log("that is empty");
    console.log(`isempty type is ${typeof isempty}`)
  }
  else if (isfull)
    console.log("that is full");
  else
    console.log("there is something in that but no full.")

  // null-object
  let Pointer = null;

  console.log(`this is Pointer, and type is ${typeof Pointer}, but this pointer is bad.`)

  // undefined

  let memory;

  console.log(`type is ${typeof memory}`)

  // Symbol TODO

}

// Array - variables that hold multiple values

if (false)
{
  const fruits1 = ['bananas', 'apples', 'oranges', 'pears'];
  const fruits2 = new Array('bananas', 'apples', 'oranges', 'pears');

  console.log('fruits1 is ' + fruits1);
  console.log('fruits2 is ' + fruits2);

  fruits1[4] = 'grapes';

  for (let i = 0; i < fruits1.length; i ++)
  {
    console.log(`${i}: ${fruits1[i]}`);
  }

  fruits2.push('mangos');
  fruits2.unshift('strawberries');
  const pop = fruits2.pop();

  for (let i = 0; i < fruits2.length; i ++)
  {
    console.log(`${i}: ${fruits2[i]}`);
  }

  console.log(`pop is ${pop}`);

  console.log(Array.isArray(fruits2));
  console.log(Array.isArray('hello'));

  console.log(fruits2.indexOf('apples'));
}


// key-value

if (false)
{
  const person = {
    firstName: 'John',
    lastName: 'Doe',
    age: 30,
    hobbies: ['music', 'movies', 'sports'],
    address: {
      street: '50 main st',
      city: 'Boston',
      state: 'MA'
    }
  };

  console.log(person.firstName, person.lastName);
  console.log(person.hobbies[1]);
  console.log(person.address);

  const { firstName, lastName, address: { city } } = person;

  console.log(firstName, lastName);
  console.log(city);

  person.email = 'jiao1751959040@gmail.com';
  console.log(person.email);

}

// array-key-value

if (false)
{
  const todos = [
    {
      id: 1,
      text: 'Take out trash',
      isCompleted: true
    },
    {
      id: 2,
      text: 'Meeting with boss',
      isCompleted: true
    },
    {
      id: 2,
      text: 'Dentist appt',
      isCompleted:false
    }
  ];

  console.log(todos[1].text)

}

// JSON convert

if (false)
{
  const todos = [
    {
      id: 1,
      text: 'Take out trash',
      isCompleted: true
    },
    {
      id: 2,
      text: 'Meeting with boss',
      isCompleted: true
    },
    {
      id: 2,
      text: 'Dentist appt',
      isCompleted:false
    }
  ];

  const todoJSON = JSON.stringify(todos);
  console.log(todoJSON);
}

// For While
if (false)
{
  for (let i = 0; i < 10; i ++)
    console.log(`The number is ${i}`);

  let i = 0;
  while(i < 10)
    console.log(`The number is ${i++}`);

  const todos = [
    {
      id: 1,
      text: 'Take out trash',
      isCompleted: true
    },
    {
      id: 2,
      text: 'Meeting with boss',
      isCompleted: true
    },
    {
      id: 2,
      text: 'Dentist appt',
      isCompleted:false
    }
  ];

  // for of
  for (let todo of todos)
  {
    console.log(todo.isCompleted);
  }

  // forEach, map. filter
  todos.forEach(function(todo) {
    console.log(todo.text);
  });

  let todoText = todos.map(function(todo) {
    return todo.text;
  });

  console.log(todoText);

  const todoCompleted = todos.filter(function(todo) {
    // ===: type and value most be equal.
    return todo.isCompleted === true;
  }).map(function(todo) {
    return todo.text;
  })

  console.log(todoCompleted);
}

// function

if (true)
{
  function addNums(num1 = 1, num2 = 1)
  {
    return num1 + num2;
  }

  console.log(addNums(1, 2));
  console.log(addNums());

  // NOTICE = =>
  const addNums2 = (num1 = 1, num2 = 1) => {
    return num1 + num2;
  }

  /*
   * const addNums2 = (num1 = 1, num2 = 1) => console.log(num1 + num2);
   * const addNums2 = (num1 = 1, num2 = 1) => num1 + num2;
   * const addNums2 = num1 => num1 + 5;
   */

  console.log(addNums2(5, 5));
}

// Object
