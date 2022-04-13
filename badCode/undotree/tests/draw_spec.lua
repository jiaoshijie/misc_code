describe("undotree", function()
  it("can be required", function()
    require('undotree.ui')
  end)
  local ui_test = require('undotree.draw')
  it("three branch", function()
    local tree = {seq=0, b={{seq=1, b={{seq=6, b={}}, {seq=2, b={{seq=3, b={{seq=5, b={}}}}}}, {seq=4, b={}}}}}}
    local info = {seq_last = 6, graph_info = tree}
    local cmp = {
      ' *',
      ' |',
      ' *',
      ' | /',
      ' | | /',
      ' | * |',
      ' | | |',
      ' | * |',
      ' | | *',
      ' | *',
      ' *',
    }
    assert.are.same(cmp, ui_test(info))
  end)
  it("three branch and two branch", function()
    local tree = {seq=0, b={{seq=1, b={{seq=6, b={}}, {seq=2, b={{seq=3, b={{seq=7, b={}}, {seq=5, b={}}}}}}, {seq=4, b={}}}}}}
    local info = {seq_last = 7, graph_info = tree }
    local cmp = {
      ' *',
      ' |',
      ' *',
      ' | /',
      ' | | /',
      ' | * |',
      ' | | |',
      ' | * |',
      ' | | / /',
      ' | | | *',
      ' | | *',
      ' * |',
      '   *',
    }
    assert.are.same(cmp, ui_test(info))
  end)
  it("more branch", function()
    local tree = {seq=0, b={{seq=1, b={{seq=8, b={}},{seq=2, b={{seq=3,b={{seq=4,b={{seq=6, b={}}, {seq=7,b={}}}},{seq=9,b={}}}}}},{seq=5, b={}}}}}}
    local info = {seq_last = 9, graph_info = tree}
    local cmp = {
      ' *',
      ' |',
      ' *',
      ' | /',
      ' | | /',
      ' | * |',
      ' | | |',
      ' | * |',
      ' | | / /',
      ' | * | |',
      ' | | / / /',
      ' | | | | *',
      ' | * | |',
      ' |   * |',
      ' *     |',
      '       *',
    }
    assert.are.same(cmp, ui_test(info))
  end)
  it('one too: three', function()
    local tree = {b={{b={{b={},seq=4},{b={{b={{b={},seq=5}},seq=3}},seq=2},{b={},seq=6}},seq=1}},seq=0}
    local info = {seq_last = 6, graph_info = tree}
    local cmp = {
      ' *',
      ' |',
      ' *',
      ' | /',
      ' | | /',
      ' | * |',
      ' | | |',
      ' | * |',
      ' * | |',
      '   * |',
      '     *',
    }
    assert.are.same(cmp, ui_test(info))
  end)
  it('one too: four', function()
    local tree = {b={{b={{b={},seq=4},{b={{b={{b={},seq=5}},seq=3}},seq=2},{b={},seq=6},{b={},seq=7}},seq=1}},seq=0}
    local info = {seq_last = 7, graph_info = tree}
    local cmp = {
      ' *',
      ' |',
      ' *',
      ' | /',
      ' | | /',
      ' | | | /',
      ' | * | |',
      ' | | | |',
      ' | * | |',
      ' * | | |',
      '   * | |',
      '     * |',
      '       *',
    }
    assert.are.same(cmp, ui_test(info))
  end)
end)
