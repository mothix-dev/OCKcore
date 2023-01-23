use std::{process::exit, env, path::{PathBuf, Path}, error::Error};
use ockcore::get_opts;

fn help() -> ! {
    eprintln!("Usage: ls [-1ahl] <directory>");
    exit(1);
}

fn main() -> Result<(), Box<dyn Error>> {
    let args: Vec<String> = env::args().collect();
    let args = args.split_at(1).1;
    let mut one_per_line = false;
    let mut show_hidden = false;
    let mut long_form = false;
    let opts = get_opts(args, "1ahl");
    if opts.as_ref().is_none() {help();}
    if opts.as_ref().unwrap().0.contains('1') {
        one_per_line = true;
    }
    if opts.as_ref().unwrap().0.contains('l') {
        one_per_line = true;
        long_form = true;
    }
    if opts.as_ref().unwrap().0.contains('a') {
        show_hidden = true;
    }
    let args = opts.unwrap().1;
    if args.is_empty() {
        ls(&env::current_dir()?, one_per_line, show_hidden, long_form)?;
    } else {
        for arg in args {
            ls(&PathBuf::from(arg), one_per_line, show_hidden, long_form)?;
        }
    }
    Ok(())
}

fn ls(pb: &Path, one_per_line: bool, show_hidden: bool, long_form: bool) -> Result<(),Box<dyn Error>> {
    if pb.is_dir() {
        for entry in pb.read_dir().unwrap().flatten() {
            ls_file(&entry.path(), one_per_line, show_hidden, long_form)?;
        }
    } else {
        ls_file(pb, one_per_line, show_hidden, long_form)?;
    }
    Ok(())
}

fn ls_file(pb: &Path, one_per_line: bool, show_hidden: bool, long_form: bool) -> Result<(),Box<dyn Error>> {
    let name = pb.file_name().unwrap().to_str().unwrap();
    let meta = pb.metadata().unwrap();
    if show_hidden || !name.starts_with('.') {
        if one_per_line {
            if long_form {
                use std::os::unix::fs::MetadataExt;
                use chrono::{TimeZone, Utc};
                if pb.is_dir() {
                    print!("d");
                } else {
                    print!("-");
                }
                use users::get_user_by_uid;
                use users::get_group_by_gid;
                let mut username = meta.uid().to_string();
                if let Some(u) = get_user_by_uid(meta.uid()) {
                    username = u.name().to_str().unwrap().to_string();
                }
                let mut groupname = meta.gid().to_string();
                if let Some(u) = get_group_by_gid(meta.gid()) {
                    groupname = u.name().to_str().unwrap().to_string();
                }
                println!("{} {} {} {} {} {} {}", mode_string(meta.mode()), meta.nlink(), username, groupname, meta.size(), Utc.timestamp_opt(meta.mtime(),0).unwrap().format("%b %d %H:%M"), name);
                
            } else {
                println!("{}", name);
            }
        } else {
            print!("{} ", name);
        }
    }
    Ok(())
}

fn mode_string(bits: u32) -> String {
    let mut mode = String::new();
    for bit in [8,7,6,5,4,3,2,1,0] {
        if bits & (1 << bit) == 0 {
            mode.push('-');
        } else {
            if bit % 3 == 0 {
                mode.push('x');
            } else if bit % 3 == 1 {
                mode.push('w');
            } else if bit % 3 == 2 {
                mode.push('r');
            }
        }
    }
    mode
}