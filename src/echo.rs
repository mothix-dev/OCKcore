use std::env;

fn main(){
    let args: Vec<String> = env::args().collect();
    let args = args.split_at(1).1;
    let mut first = true;
    match args.len() {
        0 => println!(),
        1 => println!("{}",args[0]),
        _ => for arg in args {
            if first {
                print!("{arg}");
                first = false;
            } else {
                print!(" {arg}");
            }
        }
    }
}