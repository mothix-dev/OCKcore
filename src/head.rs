use std::{process::exit, io::{stdin, BufRead, BufReader}, fs::File, env};

fn help() -> ! {
    eprintln!("Usage: head <file\"-\"> [lines]");
    eprintln!("If file is -, reads standard input.");
    eprintln!("lines defaults to 10.");
    exit(-1);
}

fn main() -> Result<(), std::io::Error> {
    let args: Vec<String> = env::args().collect();
    let args = args.split_at(1).1;
    match args.len() {
        1 if args[0].as_str() == "-" => head(stdin().lock(),10),
        1 => head::<BufReader<File>>(BufReader::new(File::open(args[0].as_str())?),10),
        2 if args[0].as_str() == "-" => head(stdin().lock(),args[1].as_str().parse::<usize>().unwrap()),
        2 => head(BufReader::new(File::open(args[0].as_str())?),args[1].as_str().parse::<usize>().unwrap()),
        _ => help()
    }
}

fn head<F: BufRead>(f: F, mut count: usize) -> Result<(),std::io::Error> {
    let lines = f.lines();
    for line in lines {
        if count == 0 {
            break;
        }
        println!("{}",line?);
        count -= 1;
    }
    Ok(())
}