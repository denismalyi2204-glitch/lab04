## Laboratory work IV

Данная лабораторная работа посвещена изучению систем непрерывной интеграции на примере сервиса **Github Actions**
## Report
```sh
export GITHUB_USERNAME="denismalyi2204-glitch"
export GITHUB_TOKEN="ваш_токен"
cd ${GITHUB_USERNAME}/workspace
pushd .
source scripts/activate
```
Задаем окружение

```sh
git clone https://github.com/${GITHUB_USERNAME}/lab03 projects/lab04
cd projects/lab04
```
Копируем репозиторий 

```sh
Cloning into 'projects/lab04'...
remote: Enumerating objects: 22, done.
remote: Counting objects: 100% (22/22), done.
remote: Compressing objects: 100% (15/15), done.
remote: Total 22 (delta 2), reused 22 (delta 2), pack-reused 0 (from 0)
Receiving objects: 100% (22/22), done.
Resolving deltas: 100% (2/2), done.
```
Вывод

```sh
git remote remove origin
git remote add origin https://github.com/${GITHUB_USERNAME}/lab04
```
Подключаем новый удаленный репозиторий

```sh
mkdir -p .github/workflows
cat > .github/workflows/ci.yml <<'EOF'
name: CI
on:
  push:
    branches: [ main, master ]
  pull_request:
    branches: [ main, master ]
jobs:
  build:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v4
    
    - name: Install CMake
      run: |
        sudo apt-get update
        sudo apt-get install -y cmake cmake-data
    
    - name: Configure
      run: cmake -H. -B_build -DCMAKE_INSTALL_PREFIX=_install
    
    - name: Build
      run: cmake --build _build
    
    - name: Install
      run: cmake --build _build --target install
EOF
cat >> README.md <<EOF
[![CI Status](https://github.com/${GITHUB_USERNAME}/lab04/actions/workflows/ci.yml/badge.svg)](https://github.com/${GITHUB_USERNAME}/lab04/actions/workflows/ci.yml)
EOF
```
Создаём папку для CI-настроек и файл конфигурации сборки, который при каждом push будет автоматически собирать проект через CMake, а затем добавляем в README бейдж со статусом сборки

```sh
git add .github/workflows/ci.yml
git add README.md
git commit -m "added CI"
git push origin main
```
Добавляем CI-конфиг и README в Git, сохраняем изменения с комментарием "added CI" и отправляем в основную ветку репозитория на GitHub

```sh
[main c323880] added CI
 2 files changed, 30 insertions(+), 1 deletion(-)
 create mode 100644 .github/workflows/ci.yml
```

```sh
Username for 'https://github.com': denismalyi2204-glitch
Password for 'https://denismalyi2204-glitch@github.com': 
Enumerating objects: 28, done.
Counting objects: 100% (28/28), done.
Delta compression using up to 4 threads
Compressing objects: 100% (19/19), done.
Writing objects: 100% (28/28), 4.44 KiB | 4.44 MiB/s, done.
Total 28 (delta 4), reused 20 (delta 2), pack-reused 0
remote: Resolving deltas: 100% (4/4), done.
To https://github.com/denismalyi2204-glitch/lab04
 * [new branch]      main -> main
branch 'main' set up to track 'origin/main'.
```
Вывод

```sh
gh auth login --with-token <<< ${GITHUB_TOKEN}
! First copy your one-time code: ****-****
Open this URL to continue in your web browser: https://../../device
✓ Authentication complete.
✓ Logged in as denismalyi2204-glitch
! You were already logged in to this account
```

```sh
gh run list
STATUS  TITLE     WORKFLOW  BRANCH  EVENT  ID           ELAPSED  AGE               
✓       added CI  CI        main    push   24412489132  23s      about 1 minute ago
```

```sh
gh run watch
found no in progress runs to watc
```

```sh
gh repo list
Showing 6 of 6 repositories in @denismalyi2204-glitch

NAME                                      DESCRIPTION                INFO    UPDATED            
denismalyi2204-glitch/lab04               Lab04 with GitHub Actions  public  about 5 minutes ago
denismalyi2204-glitch/ormpp-build-output                             public  about 1 hour ago
denismalyi2204-glitch/TAMP_2026_Denis                                public  about 3 hours ago
denismalyi2204-glitch/lab03                                          public  about 28 days ago
denismalyi2204-glitch/cpp-hello-world                                public  about 1 month ago
denismalyi2204-glitch/lab02                                          public  about 1 month ago
```

```sh
gh run list --limit 5
STATUS  TITLE     WORKFLOW  BRANCH  EVENT  ID           ELAPSED  AGE                
✓       added CI  CI        main    push   24412489132  23s      about 6 minutes ago
```

```sh
gh run list --branch main
STATUS  TITLE     WORKFLOW  BRANCH  EVENT  ID           ELAPSED  AGE                
✓       added CI  CI        main    push   24412489132  23s      about 6 minutes ago
```

```sh
gh run view
? Select a workflow run ✓ added CI, CI (main) 6m56s ago

✓ main CI · 24412489132
Triggered via push about 7 minutes ago

JOBS
✓ build in 20s (ID 71312766076)

ANNOTATIONS
! Node.js 20 actions are deprecated. The following actions are running on Node.js 20 and may not work as expected: actions/checkout@v4. Actions will be forced to run with Node.js 24 by default starting June 2nd, 2026. Node.js 20 will be removed from the runner on September 16th, 2026. Please check if updated versions of these actions are available that support Node.js 24. To opt into Node.js 24 now, set the FORCE_JAVASCRIPT_ACTIONS_TO_NODE24=true environment variable on the runner or in your workflow file. Once Node.js 24 becomes the default, you can temporarily opt out by setting ACTIONS_ALLOW_USE_UNSECURE_NODE_VERSION=true. For more information see: https://github.blog/changelog/2025-09-19-deprecation-of-node-20-on-github-actions-runners/
build: .github#2


For more information about the job, try: gh run view --job=71312766076
View this run on GitHub: https://github.com/denismalyi2204-glitch/lab04/actions/runs/24412489132
```

Авторизуемся в GitHub CLI и проверяем, что все команды работают корректно
