use std::env;

fn main(){
    let args: Vec<String> = env::args().collect();
    let args = args.split_at(1).1;
    let mut first = true;
    for arg in args {
        if first {
            print!("{arg}");
            first = false;
        } else {
            print!(" {arg}");
        }
    }
    println!();
}
