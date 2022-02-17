import React, {FC} from 'react';
import {Navigate, Routes, Route} from 'react-router-dom';

const DemoProject = React.lazy(() => import('./DemoProject'));
const StatusTab = React.lazy(() => import('./StatusTab'));
const ConfigTab = React.lazy(() => import('./ConfigTab'));
const DebugTab = React.lazy(() => import('./DebugTab'));


const ProjectRouting: FC = () => {
    return (
        <Routes>
            {
                // Add the default route for your project below
            }
            <Route path="/*" element={<Navigate to="demo/information"/>}/>
            {
                // Add your project page routes below.
            }
            <Route path="demo/*" element={<DemoProject/>}/>
            <Route path="status/*" element={<StatusTab/>}/>
            <Route path="config/*" element={<ConfigTab/>}/>
            <Route path="debug/*" element={<DebugTab/>}/>
        </Routes>
    );
};

export default ProjectRouting;
