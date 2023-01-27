use std::{env, io::stdout, io::Write};

fn yes(arg: &str) -> Result<(),std::io::Error> {
    let mut lock = stdout().lock();
    loop {
        match writeln!(lock, "{arg}") {
            Ok(_) => {},
            Err(_) => return Ok(())
        }
    }
}

fn main() -> Result<(),std::io::Error> {
    let args: Vec<String> = env::args().collect();
    let args = args.split_at(1).1;
    if args.is_empty() {
        yes("y")
    }
    else {
        yes(args[0].as_str())
    }
}