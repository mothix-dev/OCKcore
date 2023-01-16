use std::{env, io::{stdin, Read}, process::exit, fs::{File}};

fn help() -> ! {
    eprintln!("Usage: cat [-hu] [file] ...");
    eprintln!("Prints files to standard output.");
    eprintln!("If a file is - or none are provided, reads standard input.");
    eprintln!("Options:");
    eprintln!("\t-h\tshows this message.");
    eprintln!("\t-u\tignored for compatibility.");
    exit(1);
}

fn main() -> Result<(),std::io::Error> {
    let args: Vec<String> = env::args().collect();
    let args = args.split_at(1).1;
    let mut options = true;
    for arg in args {
        match arg.as_str() {
            "-h" if options => {help();}
            "-u" if options => {}
            "--" if options => {
                options = false;
            }
            "-" => {
                options = false;
                cat(stdin())?;
            }
            _ => {
                options = false;
                cat(File::open(arg)?)?;
            }
        };
    }
    if options {
        cat(stdin())?;
    }
    Ok(())
}

fn cat<F: Read>(mut f: F) -> Result<(),std::io::Error> {
    let mut s = String::new();
    f.read_to_string(&mut s)?;
    print!("{s}");
    Ok(())
}