GF_COMPLETE_DIR=/usr/local/bin
GF_METHODS=${GF_COMPLETE_DIR}/gf_methods
k=12
m=3
FAIL=

# Test all w=8
${GF_METHODS} | awk -F: '{ if ($1 == "w=8") print $2; }' |
while read method; do
  echo "Testing ${k} ${m} 8 ${method}"
  ./reed_sol_test_gf ${k} ${m} 8 ${method}
  if [[ $? != "0" ]]; then
    echo "Failed test for ${k} ${m} 8 ${method}"
    FAIL=1
    exit 1
  fi
done

if [ -n ${FAIL} ]; then
  exit 1
fi

# Test all w=16
${GF_METHODS} | awk -F: '{ if ($1 == "w=16") print $2; }' |
while read method; do
  echo "Testing ${k} ${m} 16 ${method}"
  ./reed_sol_test_gf ${k} ${m} 16 ${method}
  if [[ $? != "0" ]]; then
    echo "Failed test for ${k} ${m} 16 ${method}"
    FAIL=1
    exit 1
  fi
done

if [ -n ${FAIL} ]; then
  exit 1
fi

# Test all w=32
${GF_METHODS} | awk -F: '{ if ($1 == "w=32") print $2; }' |
while read method; do
  echo "Testing ${k} ${m} 32 ${method}"
  ./reed_sol_test_gf ${k} ${m} 32 ${method}
  if [[ $? != "0" ]]; then
    echo "Failed test for ${k} ${m} 32 ${method}"
    FAIL=1
    exit 1
  fi
done

if [ -n ${FAIL} ]; then
  exit 1
fi

echo "Passed all tests!"
