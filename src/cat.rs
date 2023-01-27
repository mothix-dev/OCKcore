use std::{env, io::{stdin, Read}, process::exit, fs::{File}};
use ockcore::get_opts;
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
    let opts = get_opts(args, "hu");
    if opts.as_ref().unwrap_or_else(||help()).0.contains('h') {help();}
    let args = opts.unwrap().1;
    if args.is_empty() {
        cat(stdin())?;
    } else {
        for arg in args {
            match arg.as_str() {
                "-" => {
                    cat(stdin())?;
                }
                _ => {
                    cat(File::open(arg)?)?;
                }
            };
        }
    }
    Ok(())
}

fn cat<F: Read>(mut f: F) -> Result<(),std::io::Error> {
    let mut s = String::new();
    f.read_to_string(&mut s)?;
    print!("{s}");
    Ok(())
}