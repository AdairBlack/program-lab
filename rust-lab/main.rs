use std::io::{self, Write};

fn main() {
    // Request the user's name
    print!("Please enter your name: ");
    // Make sure the message is immediately output
    io::stdout().flush().unwrap();
    
    let mut name = String::new();
    io::stdin().read_line(&mut name).unwrap();
    // Trim whitespace including the newline at the end
    name = name.trim().to_string();

    // Print a greeting
    println!("Hello, {}!", name);
}
