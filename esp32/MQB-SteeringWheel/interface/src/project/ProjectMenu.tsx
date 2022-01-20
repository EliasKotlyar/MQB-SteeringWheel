import { FC } from 'react';

import { List } from '@mui/material';
import SettingsRemoteIcon from '@mui/icons-material/SettingsRemote';

import { PROJECT_PATH } from '../api/env';
import LayoutMenuItem from '../components/layout/LayoutMenuItem';

const ProjectMenu: FC = () => (
  <List>
    <LayoutMenuItem icon={SettingsRemoteIcon} label="Demo" to={`/${PROJECT_PATH}/demo`} />
    <LayoutMenuItem icon={SettingsRemoteIcon} label="Status" to={`/${PROJECT_PATH}/status`} />
  </List>
);

export default ProjectMenu;
