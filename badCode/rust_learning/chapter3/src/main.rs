use std::io;

fn main() {
    convert_f_and_c();
}

#[allow(dead_code)]
fn convert_f_and_c() {
    print!("Please enter the temperatures of Fahrenheit(F) or Celsius(C) you want to convert: ");
    io::Write::flush(&mut io::stdout()).expect("flush failed!");
    let mut tem = String::new();
    io::stdin().read_line(&mut tem).expect("Failed to read line.");
    let tem = tem.trim();
    let symbol = match tem.chars().last() {
        Some(s) => s,
        None => {
            println!("Please currectly enter the temperature.");
            return;
        },
    };
    let tem: f64 = match (&tem[0..tem.len() - 1]).parse() {
        Ok(num) => num,
        Err(_) => {
            println!("Please correctly enter the temperature.");
            return;
        },
    };
    if symbol == 'f' || symbol == 'F' {
        println!("The Celsius temperature is: {:.0}°C", (tem - 32f64) * 5f64 / 9f64);  // TODO: format the output
    } else  if symbol == 'c' || symbol == 'C' {
        println!("The Fahrenheit temperature is: {:.0}°F", tem * 9f64 / 5f64 + 32f64);  // TODO: format the output
    } else {
        println!("Please currectly enter the temperature.")
    }
}

#[allow(dead_code)]
fn fibonacci(num: usize) -> u32 {
    if num == 0 {
        0
    } else if num == 1 {
        1
    } else {
        let mut arr = [0, 1, 0];
        for i in 2..num + 1 {
            arr[i % 3] = arr[(i - 1) % 3] + arr[(i - 2) % 3];
        }
        arr[num % 3]
    }
}

// Lyrics:
// On the first day of Christmas
// My true love gave to me
// A partridge in a pear tree

// On the second day of Christmas
// My true love gave to me
// Two turtle doves
// And a partridge in a pear tree

// On the third day of Christmas
// My true love gave to me
// Three French hens
// Two turtle doves
// And a partridge in a pear tree

// On the fourth day of Christmas
// My true love gave to me
// Four calling birds
// Three French hens
// Two turtle doves
// And a partridge in a pear tree

// On the fifth day of Christmas
// My true love gave to me
// Five golden rings
// Four calling birds
// Three French hens
// Two turtle doves
// And a partridge in a pear tree

// On the sixth day of Christmas
// My true love gave to me
// Six geese-a-laying
// Five golden rings
// Four calling birds
// Three French hens
// Two turtle doves
// And a partridge in a pear tree

// On the seventh day of Christmas
// My true love gave to me
// Seven swans-a-swimming
// Six geese-a-laying
// Five golden rings
// Four calling birds
// Three French hens
// Two turtle doves
// And a partridge in a pear tree

// On the eighth day of Christmas
// My true love gave to me
// Eight maids-a-milking
// Seven swans-a-swimming
// Six geese-a-laying
// Five golden rings
// Four calling birds
// Three French hens
// Two turtle doves
// And a partridge in a pear tree

// On the ninth day of Christmas
// My true love gave to me
// Nine ladies dancing
// Eight maids-a-milking
// Seven swans-a-swimming
// Six geese-a-laying
// Five golden rings
// Four calling birds
// Three French hens
// Two turtle doves
// And a partridge in a pear tree

// On the tenth day of Christmas
// My true love gave to me
// Ten lords-a-leaping
// Nine ladies dancing
// Eight maids-a-milking
// Seven swans-a-swimming
// Six geese-a-laying
// Five golden rings
// Four calling birds
// Three French hens
// Two turtle doves
// And a partridge in a pear tree

// On the eleventh of Christmas
// My true love gave to me
// Eleven pipers piping
// Ten lords-a-leaping
// Nine ladies dancing
// Eight maids-a-milking Seven swans-a-swimming
// Six geese-a-laying
// Five golden rings
// Four calling birds
// Three French hens
// Two turtle doves
// And a partridge in a pear tree

// On the twelfth day of Christmas
// My true love gave to me
// Twelve drummers drumming
// Eleven pipers piping
// Ten lords-a-leaping
// Nine ladies dancing
// Eight maids-a-milking
// Seven swans-a-swimming
// Six geese-a-laying
// Five golden rings
// Four calling birds
// Three French hens
// Two turtle doves
// And a partridge in a pear tree
// And a partridge in a pear tree
#[allow(dead_code)]
fn lyrics() {
    let days = ["first", "second", "third", "fourth", "fifth", "sixth", "seventh", "eighth", "ninth", "tenth", "eleventh", "twelfth"];
    let gifts = [
        "And a partridge in a pear tree",
        "Two turtle doves",
        "Three French hens",
        "Four calling birds",
        "Five golden rings",
        "Six geese-a-laying",
        "Seven swans-a-swimming",
        "Eight maids-a-milking",
        "Nine ladies dancing",
        "Ten lords-a-leaping",
        "Eleven pipers piping",
        "Twelve drummers drumming",
    ];
    for i in 0..12 {
        println!("On the {} day of Christmas My true love gave to me", days[i]);
        if i == 0 {
            println!("A partridge in a pear tree");
        } else {
            for j in (0..i + 1).rev() {
                println!("{}", gifts[j]);
            }
        }
        if i != 11 {
            println!();
        }
    }
    println!("And a partridge in a pear tree");
}
