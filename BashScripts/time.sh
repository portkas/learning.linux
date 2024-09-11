today()
{
    echo This is a `date +"%A %d in %B of %Y (%r)"` return
}

mkcd ()
{
  mkdir -p -- "$1" && cd -P -- "$1"
}
