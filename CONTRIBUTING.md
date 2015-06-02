Contributing to GraphBench
==========================

We're excited you want to contribute! If your change is small, please fork our repo and send a pull request.

If you have lots of things you want to change, great! Get in touch and we can talk about setting up a more involved collaboration.

What to contribute
------------------

For benchmarks/frameworks, add
- reference implementations in ```graphbench/benchmark/<framework name>```
- instructions on bulding the framework and reference implementations in ```graphbench/benchmark/<framework name>/README.md```
- (optional) create a Docker image for your framework and add a link in ```graphbench/benchmark/<framework name>/README.md```

For datasets, add
 - info in ```graphbench/data/README.md```
 - either extend ```graphbench/data/download.sh``` or add a new subdirectory with your generator or download scripts

Storing files 
------------------------

So far we have simply downloaded data that is hosted elsewhere. We may also be able to host small datasets on GitHub.

Dealing with large files
------------------------

Some datasets are prohibitively large. We suggest these are hosted on Amazon S3, under a user-pays model. More info will be provided here in the future.
