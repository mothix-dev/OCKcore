use std::{process::exit, env};

fn help() -> ! {
    eprintln!("Usage: pwd [-LPh]");
    eprintln!("Print working directory.");
    eprintln!("Defaults to relative path.");
    eprintln!("Options:");
    eprintln!("\t-L\trelative path.");
    eprintln!("\t-P\tabsolute path.");
    eprintln!("\t-h\tshows this message.");
    exit(1);
}

fn main() -> Result<(),std::io::Error> {
    let args: Vec<String> = env::args().collect();
    let args = args.split_at(1).1;
    let path = env::current_dir()?;
    let mut absolute = false;
    for arg in args {
        match arg.as_str() {
            "-h" => {help();}
            "-L" => {absolute = false;}
            "-P" => {absolute = true;}
            _ => {}
        };
    }
    if absolute {
        println!("{}",path.canonicalize()?.display());
    } else {
        println!("{}",path.display());
    }
    Ok(())
}