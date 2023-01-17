/// This function assumes you removed the executable name from the arguments.
#[must_use]
pub fn get_opts(args: &[String], switches: &str) -> Option<(String,Vec<String>)> {
    let mut opts = String::new();
    let mut end = 0;
    for arg in args {
        match arg.as_str() {
            "--" => {
                end+=1;
                break;
            },
            "-" => break,
            s if arg.starts_with('-') => {
                opts.push_str(s.split_at(1).1);
                end += 1;
            },
            _ => break
        }
    }
    if opts.chars().all(|c| switches.contains(c)) {
        Some((opts,args.split_at(end).1.to_vec()))
    } else {
        None
    }
}