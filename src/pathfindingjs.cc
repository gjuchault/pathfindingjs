#include "node.h"

#include "core/defs.hpp"

#include "core/astar.hpp"
#include "core/grid.hpp"
#include "core/smoothenPath.hpp"

#include <sstream>
#include <string>
#include <vector>

using std::vector;

namespace pathfindingjs {
    using v8::Exception;
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Number;
    using v8::Object;
    using v8::String;
    using v8::Array;
    using v8::Value;

    vector<vector<int>> map;
    int x0, y0;
    int x1, y1;
    int mapHeight, mapWidth;
    int walkerSize = 1;

    void setGrid (const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        if (args.Length() != 1) {
            isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
            return;
        }

        if (!args[0]->IsArray()) {
            isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong map")));
            return;
        }

        Local<Array> input = Local<Array>::Cast(args[0]);

        if (!input->Length() > 0) {
            isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong map")));
            return;
        }

        // Create cpp map
        Local<Array> firstRow  = Local<Array>::Cast(input->Get(0));

        mapHeight = input->Length();
        mapWidth  = firstRow->Length();

        vector<int> defaultRow = vector<int>(mapWidth, 0);
        map.resize(mapHeight, defaultRow);

        unsigned int l = input->Length();
        for (unsigned int i = 0; i < l; ++i)
        {
            Local<Array> row = Local<Array>::Cast(input->Get(i));

            unsigned int l2 = row->Length();
            for (unsigned int j = 0; j < l2; ++j)
            {
                map.at(i).at(j) = row->Get(j)->NumberValue() == 1;
            }
        }
    }

    void setWalkerSize (const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        if (args.Length() != 1) {
            isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
            return;
        }

        if (!args[0]->IsNumber()) {
            isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong position")));
            return;
        }

        walkerSize = args[0]->NumberValue();
    }

    void setFrom (const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        if (args.Length() != 2) {
            isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
            return;
        }

        if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
            isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong position")));
            return;
        }

        x0 = args[0]->NumberValue();
        y0 = args[1]->NumberValue();
    }

    void findTo (const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        if (args.Length() != 2) {
            isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
            return;
        }

        if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
            isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong position")));
            return;
        }

        x1 = args[0]->NumberValue();
        y1 = args[1]->NumberValue();

        Grid grid         = Grid_constructor(map, mapHeight, mapWidth, walkerSize);
        AStarFinder astar = AStarFinder_constructor(true, true, 1);

        vector<vector<int>> path = AStarFinder_findPath(astar, x0, y0, x1, y1, &grid);

        if (path.size() == 0) {
            args.GetReturnValue().Set(false);
        } else {
            vector<vector<int>> smoothPath = smoothenPath(&path);

            Local<Array> v8path = Array::New(isolate);
            for (unsigned int i = 0; i < smoothPath.size(); ++i) {
                Local<Array> v8row = Array::New(isolate);
                for (unsigned int j = 0; j < smoothPath.at(i).size(); ++j) {
                    Local<Number> v = Number::New(isolate, smoothPath.at(i).at(j));
                    v8row->Set(j, v);
                }

                v8path->Set(i, v8row);
            }

            args.GetReturnValue().Set(v8path);
        }
    }

    void module (Local<Object> exports) {
        NODE_SET_METHOD(exports, "setGrid", setGrid);
        NODE_SET_METHOD(exports, "setWalkerSize", setWalkerSize);
        NODE_SET_METHOD(exports, "setFrom", setFrom);
        NODE_SET_METHOD(exports, "findTo", findTo);
    }

    NODE_MODULE(pathfindingjs, module)
}
