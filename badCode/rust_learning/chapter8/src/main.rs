use rand::Rng;
use std::collections::HashMap;

fn main() {
    runq3();
}

#[allow(dead_code)]
fn runq1() {
    let mut rng = rand::thread_rng();
    let mut v: Vec<i32> = Vec::new();
    let len = 32;
    for _ in 0..len {
        v.push(rng.gen_range(0..100));
    }
    println!("{:?}", v);
    let (mid, mode) = question1(&mut v);
    match (mid, mode) {
        (Some(mi), Some(mo)) => println!("middle: {}, mode: {}", mi, mo),
        _ => println!("The list is empty!!!"),
    }
}

#[allow(dead_code)]
fn runq2() {
    let word = String::from("apple");
    let plain_word = question2(word);
    println!("{}", plain_word);
}

#[allow(dead_code)]
fn runq3() {
    let mut map: HashMap<String, Vec<String>> = HashMap::new();
    let list = vec![
        String::from("Add Sally to Engineering"),
        String::from("Add Amir to Sales"),
        String::from("Add Jiao to Sales"),
        String::from("Add Jie to Engineering"),
        String::from("Add Shi to Computer"),
    ];
    for s in list {
        question3(&mut map, s);
    }
    // get_all_employees(&map);
    // get_employees_by_dep(&map, "Wen");
}

#[allow(dead_code)]
fn question1(arr: &mut Vec<i32>) -> (Option<i32>, Option<i32>) {
    if arr.len() == 0 {
        return (None, None);
    }
    arr.sort();
    let len: usize = arr.len() as usize;
    let mid;
    if len % 2 == 0 {
        mid = arr[len / 2] + arr[len / 2 - 1];
    } else {
        mid = arr[len / 2];
    }
    let (mut count, mut c, mut mode) = (0usize, 0usize, arr[0]);
    for (i, v) in arr.iter().enumerate() {
        if i != 0 && v == &arr[i - 1] {
            count += 1;
        } else {
            if count > c {
                c = count;
                mode = arr[i - 1];
            }
            count = 0;
        }
    }
    (Some(mid), Some(mode))
}

#[allow(dead_code)]
fn question2(s: String) -> String {
    if s.len() == 0 {
        return String::from("");
    }
    let vowel = String::from("aeiou");
    let res: String;
    match vowel.find(s.chars().nth(0).unwrap()) {
        Some(_) => res = s + "-hay",
        None => res = format!("{}-{}{}", &s[1..] ,&s[0..1], "ay"),
    }
    return res;
}

#[allow(dead_code)]
fn get_name_dep(s: String) -> (String, String) {
    let s = s.split(" ");
    let (mut name, mut dep, mut is_dep) = (String::new(), String::new(), false);
    for i in s {
        if i == String::from("Add") {
            continue;
        }
        if i == String::from("to") {
            is_dep = true;
            continue;
        }
        if is_dep {
            dep += i;
        } else {
            name += i;
        }
    }
    (name, dep)
}

#[allow(dead_code)]
fn question3(map: &mut HashMap<String, Vec<String>>, s: String) {
    let (name, dep) = get_name_dep(s);
    // TODO: it's awful.
    match map.get(&dep) {
        Some(_) => {
            let v = map.entry(dep).or_insert(vec![String::new()]);
            v.push(name);
        },
        None => {
            map.insert(dep, vec![name]);
            ()
        }
    }
}

#[allow(dead_code)]
fn get_all_employees(map: &HashMap<String, Vec<String>>) {
    for (key, v) in map {
        println!("{}:", key);
        for i in v {
            println!("    {}", i);
        }
    }
}

#[allow(dead_code)]
fn get_employees_by_dep(map: &HashMap<String, Vec<String>>, dep: &str) {
    match map.get(dep) {
        Some(v) => {
            println!("{}:", dep);
            for i in v {
                println!("    {}", i);
            }
        },
        None => println!("There is no {} department!!!", dep),
    }
}
