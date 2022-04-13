let numOne = document.getElementById("num-one");
let numTwo = document.getElementById("num-two");
let addSum = document.getElementById("add-sum");

numOne.addEventListener("input", add);
numTwo.addEventListener("input", add);

function add() {
  let one = parseFloat(numOne.value) || 0;
  let two = parseFloat(numTwo.value) || 0;
  addSum.innerHTML = "Sum: " + (one + two);
}
