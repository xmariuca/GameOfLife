from fabric.api import *
from mako.template import Template
from contextlib import nested
import mako
import time
import os

env.user='ucabmrr'

env.run_at="/home/"+env.user+"/Scratch/GameOfLife/omp-output"
env.deploy_to="/home/"+env.user+"/devel/omp-gameoflife"
env.clone_url="git@github.com:xmariuca/GameOfLife.git"
env.hosts=['legion.rc.ucl.ac.uk']

modules = nested(
    prefix('module load cmake'),
    prefix('module swap compilers compilers/gnu/4.9.2'),
)

@task
def cold(branch='openmp'):
    run('rm -rf '+env.deploy_to)
    run('mkdir -p '+env.deploy_to)
    run('mkdir -p '+env.run_at)
    with cd(env.deploy_to):
        with modules:
            run('git clone '+env.clone_url)
            run('mkdir GameOfLife/build')
            with cd('GameOfLife/build'):
                run('git checkout '+branch)
                run('cmake .. ')
                run('make')
                run('tests')

@task
def warm(branch='openmp'):
  with cd(env.deploy_to+'/GameOfLife/build'):
    with modules:
        run('git checkout '+branch)
        run('git pull')
        run('cmake ..')
        run('make')
        run('tests')

@task
def patch():
  with cd(env.deploy_to+'/GameOfLife'):
    local('git diff > patch.diff')
    put('patch.diff','patch.diff')
    with modules:
        run('git checkout .')
        run('git apply patch.diff')
        with cd('build'):
            run('cmake ..')
            run('make')
            run('tests')

@task
def sub(processes=4):
    env.processes=processes
    template_file_path=os.path.join(os.path.dirname(__file__),'legion.sh.mko')
    script_local_path=os.path.join(os.path.dirname(__file__),'legion.sh')
    with open(template_file_path) as template:
        script=Template(template.read()).render(**env)
        with open(script_local_path,'w') as script_file:
            script_file.write(script)
    with cd(env.deploy_to):
        put(script_local_path,'example.sh')
        run('qsub example.sh')

@task
def stat():
    run('qstat')

@task
def wait():
  """Wait until all jobs currently qsubbed are complete, then return"""
  while "job-ID" in run('qstat'):
	time.sleep(10)

@task
def fetch():
    with lcd(os.path.join(os.path.dirname(os.path.dirname(__file__)),'results')):
      with cd(env.run_at):
        get('*')
