GF_COMPLETE_DIR=/usr/local/bin
GF_METHODS=${GF_COMPLETE_DIR}/gf_methods
ITERATIONS=128
BUFSIZE=65536
k=12
m=2

# Test all w=8
${GF_METHODS} | awk -F: '{ if ($1 == "w=8") print $2; }' |
while read method; do
  echo "Testing ${k} ${m} 8 ${ITERATIONS} ${BUFSIZE} ${method}"
  ./reed_sol_test_02 ${k} ${m} 8 ${ITERATIONS} ${BUFSIZE} ${method}
  if [[ $? != "0" ]]; then
    echo "Failed test for ${k} ${m} 8 ${ITERATIONS} ${BUFSIZE} ${method}"
    exit 1
  fi
done

# Test all w=16
${GF_METHODS} | grep -v 'TABLE' | awk -F: '{ if ($1 == "w=16") print $2; }' |
while read method; do
  echo "Testing ${k} ${m} 16 ${ITERATIONS} ${BUFSIZE} ${method}"
  ./reed_sol_test_02 ${k} ${m} 16 ${ITERATIONS} ${BUFSIZE} ${method}
  if [[ $? != "0" ]]; then
    echo "Failed test for ${k} ${m} 16 ${ITERATIONS} ${BUFSIZE} ${method}"
    exit 1
  fi
done

# Test all w=32
${GF_METHODS} | awk -F: '{ if ($1 == "w=32") print $2; }' |
while read method; do
  echo "Testing ${k} ${m} 32 ${ITERATIONS} ${BUFSIZE} ${method}"
  ./reed_sol_test_02 ${k} ${m} 32 ${ITERATIONS} ${BUFSIZE} ${method}
  if [[ $? != "0" ]]; then
    echo "Failed test for ${k} ${m} 32 ${ITERATIONS} ${BUFSIZE} ${method}"
    exit 1
  fi
done

echo "Passed all tests!"
