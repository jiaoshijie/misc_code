fn hash(s: &String, len: usize) -> usize {
    let mut h = 5381usize;
    for c in s.chars() {
        h = ((h << 5) + h) + (c as usize);
    }
    h % len
}

fn add2hash(ht: &mut [String; 16], len: usize, s: String) {
    let i = hash(&s, len);
    if ht[i] == String::from("") {
        ht[i] = s;
    } else {
        println!("Can't insert name: {}", s);
    }
}

fn cat_hash(ht: &[String; 16]) {
    println!("-------------------------------------");
    for (i, s) in ht.iter().enumerate() {
        if *s != String::from("") {
            println!("{}: {}", i, s);
        } else {
            println!("{}:", i);
        }
    }
    println!("-------------------------------------");
}

fn main() {
    let mut hash_table: [String; 16] = Default::default();
    add2hash(&mut hash_table, 16, String::from("Ada"));
    add2hash(&mut hash_table, 16, String::from("Addison"));
    add2hash(&mut hash_table, 16, String::from("Dawson"));
    add2hash(&mut hash_table, 16, String::from("Bob"));
    add2hash(&mut hash_table, 16, String::from("Edgar"));
    add2hash(&mut hash_table, 16, String::from("jiaoshijie"));
    cat_hash(&hash_table);
}
